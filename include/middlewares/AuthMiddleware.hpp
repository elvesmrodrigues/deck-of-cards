#if !defined(AUTH_MIDDLEWARE_H)
#define AUTH_MIDDLEWARE_H

#include "../models/Game.hpp"
#include "../storages/Storage.hpp"
#include "../services/Service.hpp"
#include "../../libs/server/httplib.h"
#include "../models/AuthToken.hpp"

namespace AuthMiddleware {
    bool _valid_token(const httplib::Request &req, httplib::Response &res);
    bool _game_valid(const httplib::Request &req, httplib::Response &res);
    bool _player_valid(const httplib::Request &req, httplib::Response &res);

    const Player & _get_player_from_auth_token(unsigned int &auth_token);

    // The user linked to auth token could be deleted
    bool _valid_user_from_auth_token(httplib::Response &res, unsigned int &auth_token);

    void verify_request(const httplib::Request &req, httplib::Response &res, 
                const std::function<void(const httplib::Request &, httplib::Response &, const Player &)> &callback);

    // verifies if the auth token is valid and if the requested game is of the player
    void verify_game_owner_request(const httplib::Request &req, httplib::Response &res,
                        const std::function<void(const httplib::Request &, httplib::Response &, const Player &)> &callback);

    // verifies if the auth token is valid and the identity of the player
    void verify_player_identity_request(const httplib::Request &req, httplib::Response &res,
                                   const std::function<void(const httplib::Request &, httplib::Response &, const Player &)> &callback);
}

#endif // AUTH_MIDDLEWARE_H
