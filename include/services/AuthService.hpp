#if !defined(AUTH_SERVICE_H)
#define AUTH_SERVICE_H

#include "../storages/Storage.hpp"
#include "../services/Service.hpp"
#include "../../libs/server/httplib.h"
#include "../models/AuthToken.hpp"

namespace AuthService {
    void login(const httplib::Request &req, httplib::Response &res);
    void auth_logout(const httplib::Request &req, httplib::Response &res, const Player &player);
    void add_routes(httplib::Server & server);
}

#endif // AUTH_SERVICE_H
