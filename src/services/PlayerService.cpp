#include "services/PlayerService.hpp"

namespace PlayerService {
    void create(const httplib::Request &req, httplib::Response &res) {
        field_type_list required_values = {
            std::make_pair("username", EXPECTED_TYPE_STRING),
            std::make_pair("password", EXPECTED_TYPE_STRING),
            std::make_pair("name", EXPECTED_TYPE_STRING),
        };

        if (!Service::has_required_fields(req, res, required_values))
            return;

        json data = json::parse(req.body), data_res;
        
        std::string username = data["username"];

        if (!Player::username_available(username)) {
            data_res["message"] = "The \"username\" is already in use, please choose another one.";

            res.status = HTTP_STATUS_CONFLIT;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        std::string password = data["password"];
        std::string player_name = data["name"];

        unsigned int player_id = PlayerFactory::create(username, password, player_name);

        data_res["id"] = player_id;

        res.status = HTTP_STATUS_CREATED;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_remove(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        json data, data_res;

        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Player::name, res, id))
            return;
        
        Storage &storage = Storage::get_instance();
        Player * player = (Player *) storage.retrieve(id);
        
        std::string username = player->get_username();

        Player::remove_username(username);
        storage.remove(Player::name, id);

        data_res["message"] = "Player removed succesfully.";

        res.status = HTTP_STATUS_NO_CONTENT;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_update(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Player::name, res, id))
            return;

        json data = Service::body_to_json(req), data_res;

        if (data == nullptr) {
            data_res["message"] = "Invalid JSON format.";
            
            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        field_type_list candidate_fields = {
            std::make_pair("name", EXPECTED_TYPE_STRING),
            std::make_pair("password", EXPECTED_TYPE_STRING)
        };
        std::pair<string_list, string_list> upgradable_invalid_fields = Service::get_updatable_fields(req, res, candidate_fields);

        string_list upgradable_fields = upgradable_invalid_fields.first;
        string_list invalid_fields = upgradable_invalid_fields.second;

        if (!Service::is_updatable(res, invalid_fields, upgradable_fields))
            return;

        Storage &storage = Storage::get_instance();
        Player * player = (Player *) storage.retrieve(id);

        string_list::iterator it;
        std::string updating_field;

        for (it=upgradable_fields.begin(); it != upgradable_fields.end(); it++) {
            updating_field = * it;

            if (updating_field == "name") {
                std::string new_name = data[updating_field];
                player->set_name(new_name);
            } else if (updating_field == "password") {
                std::string new_password = data[updating_field];
                player->set_password(new_password);
            } else {
                std::cout << "Invalid field: " << updating_field << std::endl;
            }
        }

        storage.update(id, player);

        data_res["message"] = "Player updated succesfully.";

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_retrieve(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        Storage & storage = Storage::get_instance();
        model_list players = storage.retrieve_all(Player::name);

        if (!players.size()) {
            res.status = HTTP_STATUS_OK;
            res.set_content("[]", JSON_RESPONSE);
            return;
        }

        model_list::iterator it;

        Player * player;
        json_list parsed_players;

        for (it = players.begin(); it != players.end(); it++) {
            player = (Player *) * it;
            parsed_players.push_back(PlayerSerializer::serialize(* player));
        }

        json data_res(parsed_players);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_retrieve_by_id(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        Storage &storage = Storage::get_instance();
        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Player::name, res, id))
            return;
        
        Player * player = (Player *) storage.retrieve(id);
        json data_res = PlayerSerializer::serialize(* player);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void add_routes(httplib::Server & server) {
        server.Post("/players", PlayerService::create);

        server.Get("/players", [](const httplib::Request &req, httplib::Response & res){ 
            AuthMiddleware::verify_request(req, res, PlayerService::auth_retrieve); 
        });

        server.Get("/players/:id", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_player_identity_request(req, res, PlayerService::auth_retrieve_by_id); 
        });

        server.Put("/players/:id", [](const httplib::Request &req, httplib::Response & res) { 
            AuthMiddleware::verify_player_identity_request(req, res, PlayerService::auth_update); 
        });

        server.Delete("/players/:id", [](const httplib::Request &req, httplib::Response &res){
            AuthMiddleware::verify_player_identity_request(req, res, PlayerService::auth_remove); 
        });
    }
} 