#if !defined(DECK_SERVICE_H)
#define DECK_SERVICE_H

#include "../factories/DeckFactory.hpp"
#include "../serializers/DeckSerializer.hpp"
#include "./Service.hpp"

namespace DeckService {
    void create(const httplib::Request &req, httplib::Response &res);
    void remove(const httplib::Request &req, httplib::Response &res);
    void update(const httplib::Request &req, httplib::Response &res);
    void retrieve(const httplib::Request &req, httplib::Response &res);
    void retrieve_by_id(const httplib::Request &req, httplib::Response &res);
};

#endif // DECK_SERVICE_H
