#if !defined(AUTH_TOKEN_H)
#define AUTH_TOKEN_H

#include "./Player.hpp"
#include "./Model.hpp"

class AuthToken : public Model {
    private:
        unsigned int _player_id;

    public:
        static std::string name;
        
        AuthToken(unsigned int player_id);

        unsigned int get_player_id();

        std::string get_class_name() override;
};

#endif // AUTH_TOKEN_H
