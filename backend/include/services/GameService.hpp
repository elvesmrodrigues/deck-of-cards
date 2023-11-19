#if !defined(GAMER_SERVICE_H)
#define GAMER_SERVICE_H

#include "./Service.hpp"

namespace GameService{
    void create(const httplib::Request &req, httplib::Response &res);
    void remove(const httplib::Request &req, httplib::Response &res);
    void update(const httplib::Request &req, httplib::Response &res);
    void retrieve(const httplib::Request &req, httplib::Response &res);
    void retrieve_by_id(const httplib::Request &req, httplib::Response &res);

    void shuffle(const httplib::Request &req, httplib::Response &res);

    void players(const httplib::Request &req, httplib::Response &res);
    void add_player(const httplib::Request &req, httplib::Response &res);
    void remove_player(const httplib::Request &req, httplib::Response &res);
    
    void add_deck(const httplib::Request &req, httplib::Response &res);
    void deal_card(const httplib::Request &req, httplib::Response &res);
    
    void count_cards_remaing_per_suit(const httplib::Request &req, httplib::Response &res);
    void count_cards_remaining(const httplib::Request &req, httplib::Response &res);
};


#endif // GAMER_SERVICE_H
