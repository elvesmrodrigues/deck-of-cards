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

#include "../../libs/server/httplib.h"
#include "../../libs/nlohmann/json.hpp"

#include "../storages/Storage.hpp"

using nlohmann::json;

namespace Service {
    unsigned int get_id_from_request(const httplib::Request &req);
    bool valid_id(httplib::Response &res, unsigned int &id);
    bool has_required_values(const httplib::Request &req, httplib::Response &res, std::list<std::string> &required_values);
}

#endif // SERVICE_H
