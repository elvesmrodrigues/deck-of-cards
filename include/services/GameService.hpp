#if !defined(GAMER_SERVICE_H)
#define GAMER_SERVICE_H

#include "./Service.hpp"

#include "../models/Card.hpp"
#include "../models/Player.hpp"

#include "../factories/GameFactory.hpp"

#include "../serializers/GameSerializer.hpp"

namespace GameService{
    json _parse_player(unsigned int &player_id);
    json _parse_player_cards(unsigned int &player_id);
    bool _player_score_comparator(const json & a, const json & b);
    
    // retrieve all games, but without sensitive data
    void retrieve(const httplib::Request &req, httplib::Response &res);
    
    void auth_create(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_remove(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_update(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_retrieve(const httplib::Request &req, httplib::Response &res, const Player &logged_player);
    void auth_retrieve_by_id(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void auth_auth_shuffle(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void auth_players(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_player_cards(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void auth_add_player(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_remove_player(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void auth_add_deck(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_decks(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void auth_deal_card(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void auth_count_cards_remaing_per_suit(const httplib::Request &req, httplib::Response &res, const Player & logged_player);
    void auth_count_cards_remaining(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void auth_get_access_code(const httplib::Request &req, httplib::Response &res, const Player & logged_player);

    void add_routes(httplib::Server &server);
};


#endif // GAMER_SERVICE_H
