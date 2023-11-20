#include "services/GameService.hpp"

namespace GameService {
    void auth_create(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        field_type_list required_values = {
            std::make_pair("access_code", EXPECTED_TYPE_STRING)
        };

        if (!Service::has_required_fields(req, res, required_values))
            return;

        json data = json::parse(req.body), data_res;

        std::string access_code = data["access_code"];
        unsigned int game_id = GameFactory::create(logged_player.get_id(), access_code);

        data_res["id"] = game_id;

        res.status = HTTP_STATUS_CREATED;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_remove(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        json data, data_res;

        Storage &storage = Storage::get_instance();

        storage.remove(Game::name, game_id);

        data_res["message"] = "Game removed succesfully.";

        res.status = HTTP_STATUS_NO_CONTENT;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_update(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        Storage & storage = Storage::get_instance();
        Game * game = (Game *) storage.retrieve(game_id);

        json data = Service::body_to_json(req), data_res;

        if (data == nullptr) {
            res.status = HTTP_STATUS_BAD_REQUEST;

            data_res["message"] = "Invalid JSON format.";
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        field_type_list candidate_fields = {std::make_pair("access_code", EXPECTED_TYPE_STRING)};
        std::pair<string_list, string_list> upgradable_invalid_fields = Service::get_updatable_fields(req, res, candidate_fields);

        string_list upgradable_fields = upgradable_invalid_fields.first;
        string_list invalid_fields = upgradable_invalid_fields.second;

        if (!Service::is_updatable(res, invalid_fields, upgradable_fields))
            return;

        string_list::iterator it;
        std::string updating_field;

        for (it=upgradable_fields.begin(); it != upgradable_fields.end(); it++) {
            updating_field = * it;

            if (updating_field == "access_code") {
                std::string new_access_code = data[updating_field];
                game->set_access_code(new_access_code);
            } 
        }

        // Only for standardization, once game is a reference to the object.
        storage.update(game_id, game);

        data_res["message"] = "Game updated succesfully.";

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }
    void retrieve(const httplib::Request &req, httplib::Response &res) {
        Storage & storage = Storage::get_instance();
        model_list games = storage.retrieve_all(Game::name);

        if (!games.size()) {
            res.status = HTTP_STATUS_OK;
            res.set_content("[]", JSON_RESPONSE);
            
            return;
        }

        model_list::iterator it;

        Game * game;
        json_list parsed_games;

        for (it = games.begin(); it != games.end(); it++) {
            game = (Game *) * it;
            
            json data;
    
            data["id"] = game->get_id();
            data["num_players"] = game->get_player_ids().size();
            data["num_decks"] = game->get_deck_ids().size();
            data["num_remaining_cards"] = game->get_card_ids().size();
            data["num_players"] = game->get_player_ids().size();
        

            parsed_games.push_back(data);
        }

        json data_res(parsed_games);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_retrieve(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        Storage & storage = Storage::get_instance();
        model_list games = storage.retrieve_all(Game::name);

        if (!games.size()) {
            res.status = HTTP_STATUS_OK;
            res.set_content("[]", JSON_RESPONSE);

            return;
        }

        model_list::iterator it;

        Game * game;
        json_list parsed_games;

        for (it = games.begin(); it != games.end(); it++) {
            game = (Game *) * it;

            if (game->get_creator() != logged_player.get_id())
                continue;

            parsed_games.push_back(GameSerializer::serialize(* game));
        }

        json data_res(parsed_games);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_retrieve_by_id(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        Storage &storage = Storage::get_instance();
        unsigned int game_id = Service::get_id_from_request(req);

        Game *game = (Game *)storage.retrieve(game_id);
        json data_res = GameSerializer::serialize(* game);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_shuffle(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        Storage & storage = Storage::get_instance();
        Game * game = (Game *) storage.retrieve(game_id);

        game->shuffle();

        json data_res;

        data_res["message"] = "The card of the game has been shuffled.";

        res.status = HTTP_STATUS_NO_CONTENT;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    json _parse_player_cards(unsigned int &player_id) {
        Storage & storage = Storage::get_instance();

        Player * player = (Player *) storage.retrieve(player_id);
        unsigned int player_score = 0;
        
        unsigned_list player_card_ids = player->get_card_ids();
        unsigned_list::iterator it;

        Card * card;
        string_list cards;
        for (it=player_card_ids.begin(); it != player_card_ids.end(); it++) {
            card = (Card *) storage.retrieve(* it);
            player_score += card->get_value();
            cards.push_back(card->repr());
        }

        json data(cards);

        return data;
    }

    json _parse_player(unsigned int &player_id) {
        Storage & storage = Storage::get_instance();

        Player * player = (Player *) storage.retrieve(player_id);
        unsigned int player_score = 0;
        
        unsigned_list player_card_ids = player->get_card_ids();
        unsigned_list::iterator it;

        Card * card;
        string_list cards;
        for (it=player_card_ids.begin(); it != player_card_ids.end(); it++) {
            card = (Card *) storage.retrieve(* it);
            player_score += card->get_value();
            cards.push_back(card->repr());
        }

        json data;

        data["id"] = player->get_id();
        data["name"] = player->get_name();
        data["username"] = player->get_username();
        data["score"] = player_score;
        data["cards"] = cards;

        return data;
    }

    bool _player_score_comparator(const json &a, const json &b) {
        return a["score"] > b["score"];
    }

    void auth_players(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        Storage &storage = Storage::get_instance();
        Game *game = (Game *)storage.retrieve(game_id);

        json_list data;

        unsigned_list player_ids = game->get_player_ids();
        unsigned_list::iterator it;

        for (it = player_ids.begin(); it != player_ids.end(); it++) 
            data.push_back(GameService::_parse_player(*it));

        data.sort(GameService::_player_score_comparator);

        json data_res(data);
        
        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_player_cards(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        unsigned int player_id = Service::get_id_from_request(req, "player_id");
        if (!Service::valid_id(Player::name, res, player_id, "player_id"))
            return;

        json data_res;

        Storage &storage = Storage::get_instance();

        Game *game = (Game *)storage.retrieve(game_id);
        Player *player = (Player *)storage.retrieve(player_id);

        if (!player->is_playing()) {
            data_res["message"] = "The player isn't in a game.";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        if (player->get_game_playing() != game->get_id()) {
            data_res["message"] = "You are not allowed to do it.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        data_res = GameService::_parse_player_cards(player_id);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_add_player(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        unsigned int player_id = Service::get_id_from_request(req, "player_id");
        if (!Service::valid_id(Player::name, res, player_id, "player_id"))
            return;

        field_type_list required_values = {
            std::make_pair("access_code", EXPECTED_TYPE_STRING)};

        if (!Service::has_required_fields(req, res, required_values))
            return;

        Storage &storage = Storage::get_instance();
        
        json data_res, data = json::parse(req.body);
        std::string access_code = data["access_code"];

        Game *game = (Game *) storage.retrieve(game_id);
        if (game->get_access_code() != access_code) {
            data_res["message"] = "Invalid access code.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        Player *player = (Player *) storage.retrieve(player_id);

        if (player->is_playing()) {
            data_res["message"] = "The player is already in a game.";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        player->enter_game(game_id);
        game->add_player(player_id);

        storage.update(player_id, player);
        storage.update(game_id, game);

        data_res["message"] = "Player added to game!";

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_remove_player(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        unsigned int player_id = Service::get_id_from_request(req, "player_id");
        if (!Service::valid_id(Player::name, res, player_id, "player_id"))
            return;

        json data_res;

        Storage &storage = Storage::get_instance();

        Game *game = (Game *)storage.retrieve(game_id);
        Player *player = (Player *)storage.retrieve(player_id);

        if (!player->is_playing()) {
            data_res["message"] = "The player isn't in a game.";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        if (player->get_id() != logged_player.get_id() && game->get_creator() != logged_player.get_id()) {
            data_res["message"] = "You are not allowed to do it.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        if (player->get_game_playing() != game->get_id()) {
            data_res["message"] = "You are not allowed to do it.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        player->leave_game();
        game->remove_player(player_id);

        storage.update(player_id, player);
        storage.update(game_id, game);

        data_res["message"] = "Player removed from game succesfully";

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_deal_card(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        unsigned int player_id = Service::get_id_from_request(req, "player_id");
        if (!Service::valid_id(Player::name, res, player_id, "player_id"))
            return;

        json data_res;

        Storage &storage = Storage::get_instance();

        Game *game = (Game *)storage.retrieve(game_id);
        Player *player = (Player *)storage.retrieve(player_id);

        if (!player->is_playing()) {
            data_res["message"] = "The player isn't in a game.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        if (player->get_game_playing() != game->get_id()) {
            data_res["message"] = "You are not allowed to do it.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        if (!game->get_card_ids().size()) {
            data_res["message"] = "There is no card do deal.";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        unsigned int card_id = game->deal_card();
        player->receive_card(card_id);

        storage.update(player_id, player);
        storage.update(game_id, game);

        data_res["message"] = "The player has received a new card.";

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_count_cards_remaing_per_suit(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        Storage & storage = Storage::get_instance();
        Game * game = (Game *) storage.retrieve(game_id);

        if (!game->get_deck_ids().size()) {
            json data_res;
            data_res["message"] = "This game there is no decks.";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        std::map<std::string, unsigned int> num_cards_per_suit = {
            {CARD_SUIT_CLUBS, 0},
            {CARD_SUIT_DIAMONDS, 0},
            {CARD_SUIT_HEARTS, 0},
            {CARD_SUIT_SPADES, 0},
        };

        unsigned_list card_ids = game->get_card_ids();
        unsigned_list::iterator card_id_it;

        Card * card;
        for (card_id_it = card_ids.begin(); card_id_it != card_ids.end(); card_id_it++) {
            card = (Card *) storage.retrieve(* card_id_it);
            num_cards_per_suit[card->get_suit()]++;
        }

        json data_res(num_cards_per_suit);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_count_cards_remaining(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        Storage & storage = Storage::get_instance();
        Game * game = (Game *) storage.retrieve(game_id);

        if (!game->get_deck_ids().size()) {
            json data_res;
            data_res["message"] = "This game there is no decks.";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);
            
            return;
        }

        nlohmann::ordered_map<std::string, nlohmann::ordered_map<std::string, unsigned int>> num_cards_per_suit_and_face;
        std::string suits[4] = {CARD_SUIT_HEARTS, CARD_SUIT_SPADES, CARD_SUIT_CLUBS, CARD_SUIT_DIAMONDS};

        for (int i=0;i<4;i++) {
            num_cards_per_suit_and_face[suits[i]] = {
                {CARD_FACE_KING, 0}, {CARD_FACE_QUEEN, 0}, {CARD_FACE_JACK, 0},
                {CARD_FACE_10, 0}, {CARD_FACE_9, 0}, {CARD_FACE_8, 0},
                {CARD_FACE_7, 0}, {CARD_FACE_6, 0}, {CARD_FACE_5, 0}, {CARD_FACE_4, 0},
                {CARD_FACE_3, 0}, {CARD_FACE_2, 0}, {CARD_FACE_ACE, 0},
            };
        }
 
        unsigned_list card_ids = game->get_card_ids();
        unsigned_list::iterator card_id_it;

        Card * card;
        for (card_id_it = card_ids.begin(); card_id_it != card_ids.end(); card_id_it++) {
            card = (Card *) storage.retrieve(* card_id_it);
            num_cards_per_suit_and_face[card->get_suit()][card->get_face()]++;
        }

        nlohmann::ordered_json data_res(num_cards_per_suit_and_face);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_get_access_code(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        Storage &storage = Storage::get_instance();
        Game *game = (Game *)storage.retrieve(game_id);

        json data_res;
        data_res["access_code"] = game->get_access_code();

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_decks(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        Storage &storage = Storage::get_instance();
        Game *game = (Game *)storage.retrieve(game_id);

        json data_res(game->get_deck_ids());

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_add_deck(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int game_id = Service::get_id_from_request(req);

        unsigned int deck_id = Service::get_id_from_request(req, "deck_id");
        if (!Service::valid_id(Deck::name, res, deck_id, "deck_id"))
            return;

        json data_res;

        Storage &storage = Storage::get_instance();
        
        Game * game = (Game *) storage.retrieve(game_id);
        Deck * deck = (Deck *) storage.retrieve(deck_id); 

        game->add_deck(* deck);

        data_res["message"] = "Deck added to game succesfully!";

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void add_routes(httplib::Server &server) {
        server.Post("/games", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_request(req, res, GameService::auth_create); 
        });    

        server.Get("/games/public", GameService::retrieve);

        server.Get("/games", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_request(req, res, GameService::auth_retrieve); 
        });    

        server.Get("/games/:id", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_retrieve_by_id); 
        });    

        server.Get("/games/:id/access_code", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_get_access_code); 
        });    

        server.Put("/games/:id", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_update); 
        });    

        server.Delete("/games/:id", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_remove); 
        });   

        server.Get("/games/:id/cards", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_count_cards_remaing_per_suit); 
        });    

        server.Get("/games/:id/cards/detailed", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_count_cards_remaining); 
        });    

        server.Put("/games/:id/cards/shuffle", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_shuffle); 
        });    

        server.Get("/games/:id/players", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_players); 
        });    

        server.Put("/games/:id/players/add/:player_id", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_request(req, res, GameService::auth_add_player); 
        });    

        server.Get("/games/:id/players/:player_id/cards", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_player_cards); 
        });    

        server.Put("/games/:id/players/:player_id/cards/deal", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_deal_card); 
        });    

        server.Put("/games/:id/players/remove/:player_id", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_request(req, res, GameService::auth_remove_player); 
        });    

        server.Get("/games/:id/decks", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_decks); 
        });    

        server.Put("/games/:id/decks/add/:deck_id", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_game_owner_request(req, res, GameService::auth_add_deck); 
        });    
    }
} 