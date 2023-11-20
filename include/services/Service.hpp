#if !defined(SERVICE_H)
#define SERVICE_H

#define JSON_RESPONSE "application/json"

#define HTTP_STATUS_OK 200
#define HTTP_STATUS_CREATED 201
#define HTTP_STATUS_NO_CONTENT 204
#define HTTP_STATUS_BAD_REQUEST 400
#define HTTP_STATUS_UNAUTHORIZED 401
#define HTTP_STATUS_FORBIDEN 403
#define HTTP_STATUS_NOT_FOUND 404
#define HTTP_STATUS_SERVER_ERROR 500
#define HTTP_STATUS_NOT_IMPLEMENTED 501

#define NO_ID_IN_REQUEST 0

#define MIN_ACCESS_CODE_SIZE 8
#define MIN_STRING_SIZE 3

// This is the only types we're using
#define EXPECTED_TYPE_STRING 1
#define EXPECTED_TYPE_NUMBER 2

#define string_list std::list<std::string>
#define field_type_list std::list<std::pair<std::string, unsigned int>>

#include <list>
#include <string>
#include <utility>

#include "../../libs/server/httplib.h"
#include "../../libs/nlohmann/json.hpp"

#include "../storages/Storage.hpp"

using nlohmann::json;

namespace Service {
    unsigned int get_id_from_request(const httplib::Request &req, const std::string & id_name = "id");
    bool valid_id(const std::string &model_name, httplib::Response &res, unsigned int &id, const std::string &id_name = "id");

    bool field_is_valid(json & data, std::pair<std::string, unsigned int> & field);
    bool has_required_fields(const httplib::Request &req, httplib::Response &res, std::list<std::pair<std::string, unsigned int>> &required_values);
    
    std::pair<string_list, string_list> get_updatable_fields(const httplib::Request &req, httplib::Response &res, std::list<std::pair<std::string, unsigned int>> &candidate_fields);

    json body_to_json(const httplib::Request &req);
    bool json_has_field(json &data, std::string &field);

    // method to avoid writing equal responses in many different classes
    bool is_updatable(httplib::Response &res, string_list &invalid_fields, string_list &updatable_fields);
}

#endif // SERVICE_H
