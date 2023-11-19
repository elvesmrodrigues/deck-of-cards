#if !defined(GAMER_SERVICE_H)
#define GAMER_SERVICE_H

#define MIN_ACCESS_CODE_SIZE 8

#include "./Service.hpp"
#include "../models/Card.hpp"
#include "../models/Player.hpp"
#include "../factories/GameFactory.hpp"
#include "../serializers/GameSerializer.hpp"

namespace GameService{
    void create(const httplib::Request &req, httplib::Response &res);
    void remove(const httplib::Request &req, httplib::Response &res);
    void update(const httplib::Request &req, httplib::Response &res);
    void retrieve(const httplib::Request &req, httplib::Response &res);
    void retrieve_by_id(const httplib::Request &req, httplib::Response &res);

    void shuffle(const httplib::Request &req, httplib::Response &res);

    json parse_player(unsigned int &player_id);

    void players(const httplib::Request &req, httplib::Response &res);
    void player_cards(const httplib::Request &req, httplib::Response &res);

    void add_player(const httplib::Request &req, httplib::Response &res);
    void remove_player(const httplib::Request &req, httplib::Response &res);

    void add_deck(const httplib::Request &req, httplib::Response &res);
    void decks(const httplib::Request &req, httplib::Response &res);

    void deal_card(const httplib::Request &req, httplib::Response &res);
    
    void count_cards_remaing_per_suit(const httplib::Request &req, httplib::Response &res);
    void count_cards_remaining(const httplib::Request &req, httplib::Response &res);

    void get_access_code(const httplib::Request &req, httplib::Response &res);
    void set_access_code(const httplib::Request &req, httplib::Response &res);

    bool player_score_comparator(const json & a, const json & b);
};


#endif // GAMER_SERVICE_H
