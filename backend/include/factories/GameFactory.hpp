#if !defined(GAME_FACTORY_H)
#define GAME_FACTORY_H

#include "../models/Game.hpp"
#include "../storages/Storage.hpp"

class GameFactory {
    public:
        static unsigned int create_game(const int creator_id);
};

#endif // GAME_FACTORY_H
