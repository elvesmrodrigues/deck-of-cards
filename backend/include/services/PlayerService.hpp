#if !defined(PLAYER_SERVICE_H)
#define PLAYER_SERVICE_H

#define MIN_SIZE_OF_PLAYER_NAME 3

#include "./Service.hpp"
#include "../serializers/PlayerSerializer.hpp"
#include "../factories/PlayerFactory.hpp"

namespace PlayerService {
    void create(const httplib::Request &req, httplib::Response &res);
    void remove(const httplib::Request &req, httplib::Response &res);
    void update(const httplib::Request &req, httplib::Response &res);
    void retrieve(const httplib::Request &req, httplib::Response &res);
    void retrieve_by_id(const httplib::Request &req, httplib::Response &res);
};

#endif // PLAYER_SERVICE_H
