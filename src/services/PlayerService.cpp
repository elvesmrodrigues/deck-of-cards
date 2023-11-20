#include "services/PlayerService.hpp"

namespace PlayerService {
    void create(const httplib::Request &req, httplib::Response &res) {
        field_type_list required_values = {std::make_pair("name", EXPECTED_TYPE_STRING)};

        if (!Service::has_required_fields(req, res, required_values))
            return;

        json data = json::parse(req.body), data_res;
        std::string player_name = data["name"];

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

        json data = Service::body_to_json(req), data_res;

        if (data == nullptr) {
            res.status = HTTP_STATUS_BAD_REQUEST;

            data_res["message"] = "Invalid JSON format.";
            res.set_content(data_res.dump(), JSON_RESPONSE);
            return;
        }

        field_type_list candidate_fields = {std::make_pair("name", EXPECTED_TYPE_STRING)};
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
            } 
        }

        storage.update(id, player);

        data_res["message"] = "Player updated succesfully.";

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void retrieve(const httplib::Request &req, httplib::Response &res) {
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