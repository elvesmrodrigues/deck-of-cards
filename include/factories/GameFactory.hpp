#if !defined(GAME_FACTORY_H)
#define GAME_FACTORY_H

#include "../utils/constants.hpp"
#include "../models/Game.hpp"
#include "../storages/Storage.hpp"

class GameFactory {
    public:
        static unsigned int create(const int creator_id, std::string access_code);
};

#endif // GAME_FACTORY_H
