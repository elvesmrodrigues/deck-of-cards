#if !defined(GAME_MODEL_H)
#define GAME_MODEL_H

#include <cstdlib>
#include <ctime>
#include <list>
#include <map>
#include <map>
#include <string>

#include "./Model.hpp"
#include "./Deck.hpp"

#include "../utils/constants.hpp"

class Game: public Model {
    private:
        unsigned int _creator_id;
        std::string _access_code;
        unsigned_list _player_ids;
        unsigned_list _deck_ids;
        unsigned_list _card_ids;

    public:
        static std::string name;

        Game(unsigned int creator_id, std::string access_code);

        unsigned int get_creator();

        void add_player(unsigned int player_id);
        void remove_player(unsigned int player_id);

        void add_deck(Deck &deck);
        void shuffle();

        unsigned_list &get_card_ids();
        unsigned_list &get_player_ids();
        unsigned_list &get_deck_ids();

        unsigned int deal_card();

        std::string get_access_code();
        void set_access_code(std::string access_code);

        std::string get_class_name() override;
};


#endif // GAME_MODEL_H
