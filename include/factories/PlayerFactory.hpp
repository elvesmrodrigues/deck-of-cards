#if !defined(PLAYER_FACTORY_H)
#define PLAYER_FACTORY_H

#include "../utils/constants.hpp"
#include "../models/Player.hpp"
#include "../storages/Storage.hpp"

class PlayerFactory {
    public:
        static unsigned int create(const std::string username, const std::string password, const std::string name);
};


#endif // PLAYER_FACTORY_H
