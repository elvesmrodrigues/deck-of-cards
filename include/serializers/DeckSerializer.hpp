#if !defined(DECK_SERIALIZER_H)
#define DECK_SERIALIZER_H

#include "../../libs/nlohmann/json.hpp"

#include "../models/Deck.hpp"
#include "../models/Card.hpp"

#include "../storages/Storage.hpp"

using nlohmann::json;

class DeckSerializer {
    public:
        static json serialize(Deck &deck);
};

#endif // DECK_SERIALIZER_H
