#include "serializers/DeckSerializer.hpp"

json DeckSerializer::serialize(Deck & deck) {
    json data;

    data["id"] = deck.get_id();
    data["cards"] = deck.get_card_ids();

    return data;
}