#if !defined(PLAYER_MODEL_H)
#define PLAYER_MODEL_H

#define NO_PLAYING 0
#define username_to_id_map std::map<std::string, unsigned int>

#include <string>
#include <list>
#include <map>

#include "./Model.hpp"

class Player: public Model {
    private:
        // unique identifier of the user
        std::string _username;
        std::string _password;

        std::string _name;

        unsigned_list _card_ids;

        // if 0, the player isn't playing.
        // A player cannot be added to different game at same time
        unsigned int _playing_game;

    public:
        static username_to_id_map user_name_to_id;
        static std::string name;

        Player(std::string username, std::string password, std::string name);

        std::string get_name();
        std::string get_username();
        std::string get_password();

        void set_name(std::string name);
        void set_password(std::string password);

        unsigned_list &get_card_ids();
        void receive_card(unsigned int card_id);
        
        bool is_playing();

        void enter_game(unsigned int game_id);
        unsigned int get_game_playing();

        void leave_game();

        static bool username_available(std::string username);

        std::string get_class_name() override;
};

#endif // PLAYER_MODEL_H
