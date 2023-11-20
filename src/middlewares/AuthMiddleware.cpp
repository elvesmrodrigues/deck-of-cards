#include "middlewares/AuthMiddleware.hpp"

namespace AuthMiddleware {
    bool _valid_token(const httplib::Request &req, httplib::Response &res) {
        std::string auth_token_str = req.get_header_value("Authorization");
        json data_res;
        
        if (!auth_token_str.size()) {  
            data_res["message"] = "Please inform a valid auth token in the \"Authorization\" header.";
            
            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);
            
            return false;
        }

        unsigned int auth_token = std::stol(auth_token_str);
        Storage & storage = Storage::get_instance();
        
        if (!storage.exists(AuthToken::name, auth_token)) {
            json data_res;

            data_res["message"] = "Invalid auth token.";
            
            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);
            
            return false;
        }

        return true;
    }

    bool _game_valid(const httplib::Request &req, httplib::Response &res) {
        unsigned int id = Service::get_id_from_request(req);
        return Service::valid_id(Game::name, res, id);
    }

    bool _player_valid(const httplib::Request &req, httplib::Response &res) {
        unsigned int id = Service::get_id_from_request(req);
        return Service::valid_id(Player::name, res, id);
    }

    bool _valid_user_from_auth_token(httplib::Response &res, unsigned int &auth_token) {
        Storage &storage = Storage::get_instance();

        if (!storage.exists(AuthToken::name, auth_token)) {
            json data_res;

            data_res["message"] = "Invalid auth token.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return false;
        }

        AuthToken *token = (AuthToken *)storage.retrieve(auth_token);
        unsigned int player_id = token->get_player_id();

        if (!storage.exists(Player::name, player_id)) {
            storage.remove(AuthToken::name, auth_token);
            
            json data_res;
            data_res["message"] = "Invalid auth token.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return false;
        }

        return true;
    }

    const Player & _get_player_from_auth_token(unsigned int &auth_token) {
        Storage & storage = Storage::get_instance();

        AuthToken *token = (AuthToken *) storage.retrieve(auth_token);
        unsigned int player_id = token->get_player_id();

        Player * player = (Player *)storage.retrieve(player_id);

        return * player;
    }

    void verify_request(const httplib::Request &req, httplib::Response &res, const std::function<void(const httplib::Request &, httplib::Response &, const Player &)> & callback) {
        if (!AuthMiddleware::_valid_token(req, res))
            return;

        unsigned int auth_token = std::stol(req.get_header_value("Authorization"));
        if (!AuthMiddleware::_valid_user_from_auth_token(res, auth_token)) 
            return;

        Player player = AuthMiddleware::_get_player_from_auth_token(auth_token);

        callback(req, res, player);
    }

    // verifies if the auth token is valid and if the requested game is of the player
    void verify_game_owner_request(const httplib::Request &req, httplib::Response &res, const std::function<void(const httplib::Request &, httplib::Response &, const Player &)> &callback) {
        if (!AuthMiddleware::_valid_token(req, res))
            return;

        if (!AuthMiddleware::_game_valid(req, res))
            return;

        unsigned int auth_token = std::stol(req.get_header_value("Authorization"));
        if (!AuthMiddleware::_valid_user_from_auth_token(res, auth_token))
            return;

        Player player = AuthMiddleware::_get_player_from_auth_token(auth_token);

        Storage & storage = Storage::get_instance();

        unsigned int game_id = Service::get_id_from_request(req);
        Game * game = (Game *) storage.retrieve(game_id);

        if (game->get_creator() != player.get_id()) {
            json data_res;

            data_res["message"] = "You are not the owner of the game.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        } 

        callback(req, res, player);
    }

    void verify_player_identity_request(const httplib::Request &req, httplib::Response &res, const std::function<void(const httplib::Request &, httplib::Response &, const Player &)> &callback) {
        if (!AuthMiddleware::_valid_token(req, res))
            return;

        if (!AuthMiddleware::_player_valid(req, res))
            return;

        unsigned int auth_token = std::stol(req.get_header_value("Authorization"));
        if (!AuthMiddleware::_valid_user_from_auth_token(res, auth_token))
            return;

        Player player_from_token = AuthMiddleware::_get_player_from_auth_token(auth_token);

        Storage &storage = Storage::get_instance();

        unsigned int player_id_from_req_param = Service::get_id_from_request(req);
        Player * player_from_req_param = (Player *) storage.retrieve(player_id_from_req_param); 

        if (player_from_token.get_id() != player_from_req_param->get_id()) {
            json data_res;

            data_res["message"] = "Invalid auth token.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        callback(req, res, player_from_token);
    }
}