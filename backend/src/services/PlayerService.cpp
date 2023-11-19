#include "services/PlayerService.hpp"

namespace PlayerService {
    void create(const httplib::Request &req, httplib::Response &res) {
        std::list<std::string> required_values = {"name"};

        if (!Service::has_required_values(req, res, required_values))
            return;

        json data = json::parse(req.body), data_res;

        if (!data["name"].is_string()) {
            res.status = HTTP_STATUS_BAD_REQUEST;
            data_res["message"] = "The field name must be a string.";
            res.set_content(data_res.dump(), JSON_RESPONSE);
        }

        std::string player_name = data["name"];

        if (player_name.size() < MIN_SIZE_OF_PLAYER_NAME) {
            res.status = HTTP_STATUS_BAD_REQUEST;
            data_res["message"] = "The field name must be a string with at least " + std::to_string(MIN_SIZE_OF_PLAYER_NAME) + " characters.";
            res.set_content(data_res.dump(), JSON_RESPONSE);
            return;
        }

        unsigned int player_id = PlayerFactory::create(player_name);

        data_res["id"] = player_id;

        res.status = HTTP_STATUS_CREATED;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void remove(const httplib::Request &req, httplib::Response &res) {
        json data, data_res;

        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Player::name, res, id))
            return;
        
        Storage &storage = Storage::get_instance();
        
        storage.remove(Player::name, id);
        
        data_res["message"] = "Player removed succesfully.";

        res.status = HTTP_STATUS_NO_CONTENT;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void update(const httplib::Request &req, httplib::Response &res) {
        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Player::name, res, id))
            return;

        std::list<std::string> required_values = {"name"};

        if (!Service::has_required_values(req, res, required_values))
            return;

        json data = json::parse(req.body), data_res;

        if (!data["name"].is_string()) {
            res.status = HTTP_STATUS_BAD_REQUEST;
            data_res["message"] = "The field name must be a string.";
            res.set_content(data_res.dump(), JSON_RESPONSE);
        }

        std::string player_name = data["name"];

        if (player_name.size() < MIN_SIZE_OF_PLAYER_NAME) {
            res.status = HTTP_STATUS_BAD_REQUEST;
            data_res["message"] = "The field name must be a string with at least " + std::to_string(MIN_SIZE_OF_PLAYER_NAME) + " characters.";
            res.set_content(data_res.dump(), JSON_RESPONSE);
            return;
        }

        Storage &storage = Storage::get_instance();

        Player * player = (Player *) storage.retrieve(id);
        player->set_name(player_name);

        storage.update(id, player);

        data_res["message"] = "Player updated succesfully.";

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void retrieve(const httplib::Request &req, httplib::Response &res) {
        Storage & storage = Storage::get_instance();
        std::list<Model *> players = storage.retrieve_all(Player::name);

        if (!players.size()) {
            res.status = HTTP_STATUS_OK;
            res.set_content("[]", JSON_RESPONSE);
            return;
        }

        std::list<Model *>::iterator it;

        Player * player;
        std::list<json> parsed_players;

        for (it = players.begin(); it != players.end(); it++) {
            player = (Player *) * it;
            parsed_players.push_back(PlayerSerializer::serialize(* player));
        }

        json data_res(parsed_players);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void retrieve_by_id(const httplib::Request &req, httplib::Response &res) {
        Storage &storage = Storage::get_instance();
        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Player::name, res, id))
            return;
        
        Player * player = (Player *) storage.retrieve(id);
        json data_res = PlayerSerializer::serialize(* player);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }
} 