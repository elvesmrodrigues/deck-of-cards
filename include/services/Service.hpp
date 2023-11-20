#if !defined(SERVICE_H)
#define SERVICE_H

#define JSON_RESPONSE "application/json"

#include <list>
#include <string>
#include <utility>

#include "../utils/constants.hpp"
#include "../middlewares/AuthMiddleware.hpp"
#include "../storages/Storage.hpp"

#include "../../libs/server/httplib.h"
#include "../../libs/nlohmann/json.hpp"

using nlohmann::json;

namespace Service {
    unsigned int get_id_from_request(const httplib::Request &req, const std::string & id_name = "id");
    bool valid_id(const std::string &model_name, httplib::Response &res, unsigned int &id, const std::string &id_name = "id");

    bool field_is_valid(json & data, std::pair<std::string, unsigned int> & field);
    bool has_required_fields(const httplib::Request &req, httplib::Response &res, field_type_list &required_values);
    
    std::pair<string_list, string_list> get_updatable_fields(const httplib::Request &req, httplib::Response &res, field_type_list &candidate_fields);

    json body_to_json(const httplib::Request &req);
    bool json_has_field(json &data, std::string &field);

    // method to avoid writing equal responses in many different classes
    bool is_updatable(httplib::Response &res, string_list &invalid_fields, string_list &updatable_fields);
}

#endif // SERVICE_H
