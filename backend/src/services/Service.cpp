#include "services/Service.hpp"

namespace Service {
    unsigned int get_id_from_request(const httplib::Request &req) {
        try {
            return std::stoul(req.path_params.at("id"));
        } catch (const std::out_of_range &e) {   
            return NO_ID_IN_REQUEST;
        } 
    }

    bool valid_id(httplib::Response &res, unsigned int &id) {
        Storage &storage = Storage::get_instance();

        json data;
        if (id == NO_ID_IN_REQUEST) {
            data["message"] = "Please, inform the ID of the item to be removed.";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data.dump(), JSON_RESPONSE);

            return false;
        }

        if (!storage.exists(id)) {
            data["message"] = "There is no item with the informed ID: " + std::to_string(id) + ".";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data.dump(), JSON_RESPONSE);

            return false;
        }

        return true;
    }

    bool has_required_values(const httplib::Request &req, httplib::Response &res, std::list<std::string> &required_values) {
        json data, data_res;

        try {
            data = json::parse(req.body);
        } catch (const json::parse_error &e) {
            res.status = HTTP_STATUS_BAD_REQUEST;

            data_res["message"] = "Invalid JSON format.";
            res.set_content(data_res.dump(), JSON_RESPONSE);
            return false;
        }

        std::list<std::string>::iterator req_val_it;

        for (req_val_it = required_values.begin(); req_val_it != required_values.end(); req_val_it++) {
            if (data.find(* req_val_it) == data.end()) {
                res.status = HTTP_STATUS_BAD_REQUEST;
                
                data_res["message"] = "The field \"" + *req_val_it + "\" is required.";
                res.set_content(data_res.dump(), JSON_RESPONSE);
                
                return false;
            }
        }

        return true;
    }
}