#if !defined(PLAYER_MODEL_H)
#define PLAYER_MODEL_H

#define NO_PLAYING 0

#include <string>
#include <list>

#include "./Model.hpp"

class Player: public Model {
    private:
        std::string _name;
        std::list<unsigned int> _card_ids;

        // if 0, the player isn't playing.
        // A player cannot be added to different game at same time
        unsigned int _playing_game;

    public:
        static std::string name;

        Player(std::string name);

        std::string get_name();
        void set_name(std::string name);

        std::list<unsigned int> &get_card_ids();
        void receive_card(unsigned int card_id);
        
        bool is_playing();

        void enter_game(unsigned int game_id);
        unsigned int get_game_playing();

        void leave_game();

        std::string get_class_name() override;
};

#endif // PLAYER_MODEL_H
