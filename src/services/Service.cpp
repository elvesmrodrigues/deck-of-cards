#include "services/Service.hpp"

namespace Service {
    unsigned int get_id_from_request(const httplib::Request &req, const std::string & id_name) {
        try {
            return std::stoul(req.path_params.at(id_name));
        } catch (const std::out_of_range &e) {   
            return NO_ID_IN_REQUEST;
        } 
    }

    bool valid_id(const std::string &model_name, httplib::Response &res, unsigned int &id, const std::string &id_name) {
        Storage &storage = Storage::get_instance();

        json data;
        if (id == NO_ID_IN_REQUEST) {
            data["message"] = "Please, inform \"" + id_name + "\".";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data.dump(), JSON_RESPONSE);

            return false;
        }

        if (!storage.exists(model_name, id)) {
            data["message"] = "There is no item with the informed \"" + id_name + "\" " + std::to_string(id) + ".";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data.dump(), JSON_RESPONSE);

            return false;
        }

        return true;
    }

    bool has_required_fields(const httplib::Request &req, httplib::Response &res, std::list<std::string> &required_values) {
        json data_res, data = Service::body_to_json(req);

        if (data == nullptr) {
            res.status = HTTP_STATUS_BAD_REQUEST;

            data_res["message"] = "Invalid JSON format.";
            res.set_content(data_res.dump(), JSON_RESPONSE);
            return false;
        }

        std::list<std::string>::iterator req_val_it;

        for (req_val_it = required_values.begin(); req_val_it != required_values.end(); req_val_it++) {
            if (!Service::json_has_field(data, * req_val_it)) {
                res.status = HTTP_STATUS_BAD_REQUEST;
                
                data_res["message"] = "The field \"" + * req_val_it + "\" is required.";
                res.set_content(data_res.dump(), JSON_RESPONSE);
                
                return false;
            }
        }

        return true;
    }

    json body_to_json(const httplib::Request &req) {
        try {
            return json::parse(req.body);
            
        } catch (const json::parse_error &e) {
            return nullptr;
        }
    }

    bool json_has_field(json &data, std::string &field) {
        return data.find(field) != data.end();
    }
}