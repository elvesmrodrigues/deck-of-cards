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

    bool field_is_valid(json & data, std::pair<std::string, unsigned int> & field) {
        json data_res;

        std::string field_val, req_field = field.first;
        unsigned int expected_type = field.second;

        switch (expected_type) {
            case EXPECTED_TYPE_STRING:
                if (!data[req_field].is_string()) 
                    return false;
                
                // it's needed to get the data value to check the size
                field_val = data[req_field]; 

                if (field_val.size() < MIN_STRING_SIZE)
                    return false;
            
                break;
            
            case EXPECTED_TYPE_NUMBER:
                if (!data[req_field].is_number())
                    return false;
                
                break;

            default:
                break;
        }

        return true;
    }

    bool has_required_fields(const httplib::Request &req, httplib::Response &res, std::list<std::pair<std::string, unsigned int>> &required_values) {
        json data_res, data = Service::body_to_json(req);

        if (data == nullptr) {
            res.status = HTTP_STATUS_BAD_REQUEST;

            data_res["message"] = "Invalid JSON format.";
            res.set_content(data_res.dump(), JSON_RESPONSE);
            return false;
        }

        std::string req_field;
        std::list<std::pair<std::string, unsigned int>>::iterator it;

        for (it = required_values.begin(); it != required_values.end(); it++) {
            req_field = it->first;
   
            if (!Service::json_has_field(data, req_field)) {
                res.status = HTTP_STATUS_BAD_REQUEST;
                
                data_res["message"] = "The field \"" + req_field + "\" is required.";
                res.set_content(data_res.dump(), JSON_RESPONSE);
                
                return false;
            }

            if (!Service::field_is_valid(data, * it)) {
                data_res["message"] = "Please, informe a valid value for the field \"" + req_field + "\"."; 
                res.status = HTTP_STATUS_BAD_REQUEST;
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

    std::pair<string_list, string_list> get_updatable_fields(const httplib::Request &req, httplib::Response & res, std::list<std::pair<std::string, unsigned int>> &candidate_fields) {
        string_list updatable_fields;
        string_list invalid_fields;

        json data_res, data = Service::body_to_json(req);

        if (data == nullptr) 
            return std::make_pair(updatable_fields, invalid_fields);
        
        std::string candidate_field;
        std::list<std::pair<std::string, unsigned int>>::iterator it;

        for (it=candidate_fields.begin(); it != candidate_fields.end(); it++) {
            candidate_field = it->first;

            if (Service::json_has_field(data, candidate_field)) {
                if (!Service::field_is_valid(data, * it)) 
                    invalid_fields.push_back(candidate_field); //empty
                updatable_fields.push_back(candidate_field); 
            }

        }

        return std::make_pair(updatable_fields, invalid_fields);
    }

    bool is_updatable(httplib::Response &res, string_list &invalid_fields, string_list &updatable_fields) {
        if (invalid_fields.size()) {
            json data_res;

            data_res["message"] = "Please, check the invalid fields.";
            data_res["invalid_fields"] = invalid_fields;

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return false;
        }

        if (!updatable_fields.size()) {
            json data_res;

            data_res["message"] = "There is no fields to update.";

            res.status = HTTP_STATUS_BAD_REQUEST;
            res.set_content(data_res.dump(), JSON_RESPONSE);

            return false;
        }

        return true;
    }
}