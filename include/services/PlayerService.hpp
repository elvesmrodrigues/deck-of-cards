#if !defined(PLAYER_SERVICE_H)
#define PLAYER_SERVICE_H

#include "./Service.hpp"

#include "../models/Player.hpp"
#include "../serializers/PlayerSerializer.hpp"
#include "../factories/PlayerFactory.hpp"

namespace PlayerService {
    void create(const httplib::Request &req, httplib::Response &res);
    void auth_remove(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_update(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_retrieve(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_retrieve_by_id(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void add_routes(httplib::Server &server);
};

#endif // PLAYER_SERVICE_H
