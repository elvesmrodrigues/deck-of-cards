#if !defined(PLAYER_FACTORY_H)
#define PLAYER_FACTORY_H

#include "../models/Player.hpp"
#include "../storages/Storage.hpp"

class PlayerFactory {
    public:
        static unsigned int create_player(const std::string name);         
};


#endif // PLAYER_FACTORY_H
