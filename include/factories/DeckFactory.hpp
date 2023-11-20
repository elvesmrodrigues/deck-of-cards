#if !defined(DECK_FACTORY_H)
#define DECK_FACTORY_H

#include <list>
#include <string>

#include "../utils/constants.hpp"
#include "../models/Card.hpp"
#include "../models/Deck.hpp"
#include "../storages/Storage.hpp"

class DeckFactory {
    public:
        static unsigned int create();
};


#endif // DECK_FACTORY_H
