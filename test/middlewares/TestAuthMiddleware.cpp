#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../libs/doctest/doctest.h"
#include "../../libs/server/httplib.h"

#include "../../include/models/AuthToken.hpp"
#include "../../include/storages/Storage.hpp"
#include "../../include/services/Service.hpp"
#include "../../include/models/Game.hpp"

#include "../../include/middlewares/AuthMiddleware.hpp"

TEST_CASE("Verifies token validation") {
    httplib::Request req;
    httplib::Response res;

    SUBCASE("Checks if middleware can verify if a token is valid") {
        AuthToken token(1);
        Storage &storage = Storage::get_instance();
        storage.save(& token);

        req.set_header("Authorization", "1");

        CHECK(AuthMiddleware::_valid_token(req, res));

        unsigned int auth_token = std::stol(req.get_header_value("Authorization"));
        storage.remove(AuthToken::name, auth_token);
    }

    SUBCASE("Checks if middleware can verify if a token is invalid") {
        req.set_header("Authorization", "1");
        CHECK(!AuthMiddleware::_valid_token(req, res));
    }
}

TEST_CASE ("Verifies game validation") {
    httplib::Request req;
    httplib::Response res;

    SUBCASE("Checks if middleware can verify if a game is valid") {
        Game game(1, "game");
        Storage &storage = Storage::get_instance();
        unsigned int game_id = storage.save(& game);

        req.path_params["id"] = std::to_string(game_id);

        CHECK(AuthMiddleware::_game_valid(req, res));

        storage.remove(Game::name, game_id);
    }

    SUBCASE("Checks if middleware can verify if a game is invalid") {
        // the game id is not in the request
        CHECK(!AuthMiddleware::_game_valid(req, res));
        
        // the game id does not exist
        req.path_params["id"] = "1";
        CHECK(!AuthMiddleware::_game_valid(req, res));
    }
}

TEST_CASE ("Verifies player validation") {
    httplib::Request req;
    httplib::Response res;

    SUBCASE("Checks if middleware can verify if a player is valid") {
        Player player("username", "pass", "player");
        Storage &storage = Storage::get_instance();
        unsigned int player_id = storage.save(& player);

        req.path_params["id"] = std::to_string(player_id);

        CHECK(AuthMiddleware::_player_valid(req, res));

        storage.remove(Player::name, player_id);
    }

    SUBCASE("Checks if middleware can verify if a player is invalid") {
        // the player id is not in the request
        CHECK(!AuthMiddleware::_player_valid(req, res));
        
        // the player id does not exist
        req.path_params["id"] = "1";
        CHECK(!AuthMiddleware::_player_valid(req, res));
    }
}

TEST_CASE ("Verifies if can get the logged user") {
    httplib::Request req;
    httplib::Response res;

    SUBCASE("Checks if middleware can get the logged user") {
        Storage &storage = Storage::get_instance();
        
        Player *player = new Player("username", "pass", "player");
        unsigned int player_id = storage.save(player);

        AuthToken *token = new AuthToken(player_id);
        unsigned int auth_token = storage.save(token);

        req.set_header("Authorization", std::to_string(auth_token));

        CHECK(AuthMiddleware::_valid_user_from_auth_token(res, auth_token));

        storage.remove(Player::name, player_id);
        storage.remove(AuthToken::name, auth_token);
    }

    SUBCASE("Checks if middleware can get the logged user when the token is invalid") {
        unsigned int auth_token = 1;
        CHECK(!AuthMiddleware::_valid_user_from_auth_token(res, auth_token));
    }
}

TEST_CASE ("Checks if a request is authenticated") {
    httplib::Request req;
    httplib::Response res;

    SUBCASE("Checks if middleware can verify if a request is authenticated") {
        Storage &storage = Storage::get_instance();
        
        Player *player = new Player("username", "pass", "player");
        unsigned int player_id = storage.save(player);

        AuthToken *token = new AuthToken(player_id);
        unsigned int auth_token = storage.save(token);

        req.set_header("Authorization", std::to_string(auth_token));

        AuthMiddleware::verify_request(req, res, [](const httplib::Request &req, httplib::Response &res, const Player &player) {
            CHECK(true);
        });

        storage.remove(Player::name, player_id);
        storage.remove(AuthToken::name, auth_token);
    }

    SUBCASE("Checks if middleware can verify if a request is not authenticated") {
        AuthMiddleware::verify_request(req, res, [](const httplib::Request &req, httplib::Response &res, const Player &player) {
            CHECK(false);
        });
    }
}

TEST_CASE ("Checks ownership of a game") {
    httplib::Request req;
    httplib::Response res;

    SUBCASE("Checks if middleware can verify if a request is authenticated and the game is of the player") {
        Storage &storage = Storage::get_instance();
        
        Player *player = new Player("username", "pass", "player");
        unsigned int player_id = storage.save(player);

        AuthToken *token = new AuthToken(player_id);
        unsigned int auth_token = storage.save(token);

        Game *game = new Game(player_id, "game");
        unsigned int game_id = storage.save(game);

        req.set_header("Authorization", std::to_string(auth_token));
        req.path_params["id"] = std::to_string(game_id);

        AuthMiddleware::verify_game_owner_request(req, res, [](const httplib::Request &req, httplib::Response &res, const Player &player) {
            CHECK(true);
        });

        storage.remove(Player::name, player_id);
        storage.remove(AuthToken::name, auth_token);
        storage.remove(Game::name, game_id);
    }

    SUBCASE("Checks if middleware can verify if a request is authenticated and the game is not of the player") {
        Storage &storage = Storage::get_instance();
        
        Player *player = new Player("username", "pass", "player");
        unsigned int player_id = storage.save(player);

        AuthToken *token = new AuthToken(player_id);
        unsigned int auth_token = storage.save(token);

        Game *game = new Game(player_id + 1, "game");
        unsigned int game_id = storage.save(game);

        req.set_header("Authorization", std::to_string(auth_token));
        req.path_params["id"] = std::to_string(game_id);

        AuthMiddleware::verify_game_owner_request(req, res, [](const httplib::Request &req, httplib::Response &res, const Player &player) {
            CHECK(false);
        });

        storage.remove(Player::name, player_id);
        storage.remove(AuthToken::name, auth_token);
        storage.remove(Game::name, game_id);
    }

}

TEST_CASE ("Check the identity of the player request") {
    httplib::Request req;
    httplib::Response res;

    SUBCASE("Checks if middleware can verify if a request is authenticated and the player is the same of the token") {
        Storage &storage = Storage::get_instance();
        
        Player *player = new Player("username", "pass", "player");
        unsigned int player_id = storage.save(player);

        AuthToken *token = new AuthToken(player_id);
        unsigned int auth_token = storage.save(token);

        req.set_header("Authorization", std::to_string(auth_token));
        req.path_params["id"] = std::to_string(player_id);

        AuthMiddleware::verify_player_identity_request(req, res, [](const httplib::Request &req, httplib::Response &res, const Player &player) {
            CHECK(true);
        });

        storage.remove(Player::name, player_id);
        storage.remove(AuthToken::name, auth_token);
    }

    SUBCASE("Checks if middleware can verify if a request is authenticated and the player is not the same of the token") {
        Storage &storage = Storage::get_instance();
        
        Player *player = new Player("username", "pass", "player");
        unsigned int player_id = storage.save(player);

        AuthToken *token = new AuthToken(player_id);
        unsigned int auth_token = storage.save(token);

        req.set_header("Authorization", std::to_string(auth_token));
        req.path_params["id"] = std::to_string(player_id + 1);

        AuthMiddleware::verify_player_identity_request(req, res, [](const httplib::Request &req, httplib::Response &res, const Player &player) {
            CHECK(false);
        });

        storage.remove(Player::name, player_id);
        storage.remove(AuthToken::name, auth_token);
    }
}