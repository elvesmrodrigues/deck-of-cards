#include "services/AuthService.hpp"

namespace AuthService {
    void login(const httplib::Request &req, httplib::Response &res) {
        field_type_list required_values = {
            std::make_pair("username", EXPECTED_TYPE_STRING),
            std::make_pair("password", EXPECTED_TYPE_STRING)};

        if (!Service::has_required_fields(req, res, required_values))
            return;

        json data = json::parse(req.body), data_res;
        std::string username = data["username"];

        // if the username available, is because the player don't exists 
        if (Player::username_available(username)) {
            data_res["message"] = "The player don't exists.";

            res.status = HTTP_STATUS_NOT_FOUND;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        unsigned int player_id = Player::user_name_to_id[username];

        Storage & storage = Storage::get_instance();
        Player * player = (Player *) storage.retrieve(player_id);

        std::string password = data["password"];

        if (player->get_password() != password) {
            data_res["message"] = "Incorrect password.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        unsigned int auth_token = storage.save(new AuthToken(player_id));
        data_res["auth_token"] = auth_token;

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_logout(const httplib::Request &req, httplib::Response &res, const Player &player) {
        json data_res;
        
        unsigned int auth_token = std::stol(req.get_header_value("Authorization"));
        Storage & storage = Storage::get_instance();

        if (!storage.exists(AuthToken::name, auth_token)) {
            data_res["message"] = "Invalid auth token.";

            res.status = HTTP_STATUS_UNAUTHORIZED;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return;
        }

        storage.remove(AuthToken::name, auth_token);

        data_res["message"] = "The user has successfully logged out";
        
        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void add_routes(httplib::Server & server) {
        server.Post("/auth/login", AuthService::login);
        server.Post("/auth/logout", [](const httplib::Request &req, httplib::Response &res) {
            AuthMiddleware::verify_request(req, res, AuthService::auth_logout);
        });
    }
}
