#if !defined(GAME_SERIALIZER_H)
#define GAME_SERIALIZER_H

#include "../../libs/nlohmann/json.hpp"
#include "../models/Game.hpp"
#include "../models/Card.hpp"
#include "../storages/Storage.hpp"

using nlohmann::json;

class GameSerializer {
    public:
        static json serialize(Game &game);
};


#endif // GAME_SERIALIZER_H
