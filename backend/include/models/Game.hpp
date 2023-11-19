#if !defined(GAME_MODEL_H)
#define GAME_MODEL_H

#define NO_CARD 0 

#include <cstdlib>
#include <ctime>
#include <string>
#include <list>
#include <map>
#include <map>

#include "./Model.hpp"
#include "./Deck.hpp"

class Game: public Model {
    private:
        unsigned int _creator_id;
        std::string _access_code;
        std::list<unsigned int> _player_ids;
        std::list<unsigned int> _deck_ids;
        std::list<unsigned int> _card_ids;

    public:
        static std::string name;

        Game(unsigned int creator_id, std::string access_code);

        unsigned int get_creator();

        void add_player(unsigned int player_id);
        void remove_player(unsigned int player_id);

        void add_deck(Deck &deck);
        void shuffle();

        std::list<unsigned int> &get_card_ids();
        std::list<unsigned int> &get_player_ids();
        std::list<unsigned int> &get_deck_ids();

        unsigned int deal_card();

        std::string get_access_code();
        void set_access_code(std::string access_code);

        std::string get_class_name() override;
};


#endif // GAME_MODEL_H
