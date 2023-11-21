#if !defined(DECK_SERVICE_H)
#define DECK_SERVICE_H

#include "./Service.hpp"
#include "../models/Player.hpp"
#include "../factories/DeckFactory.hpp"
#include "../serializers/DeckSerializer.hpp"

namespace DeckService {
    void auth_create(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_remove(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_update(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_retrieve(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_retrieve_by_id(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void add_routes(httplib::Server &server);
};

#endif // DECK_SERVICE_H
