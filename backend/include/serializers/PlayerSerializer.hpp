#if !defined(PLAYER_SERIALIZER_H)
#define PLAYER_SERIALIZER_H

#include "../../libs/nlohmann/json.hpp"

#include "../models/Player.hpp"

using nlohmann::json;

class PlayerSerializer {
    public:
        static json serialize(Player & player);
};

#endif // PLAYER_SERIALIZER_H
