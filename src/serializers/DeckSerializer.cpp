#include "serializers/DeckSerializer.hpp"

json DeckSerializer::serialize(Deck & deck) {
    json data;

    Storage &storage = Storage::get_instance();

    std::list<unsigned int> card_ids = deck.get_card_ids();
    std::list<unsigned int>::iterator it;

    Card * card;
    std::list<std::string> cards;
    for (it = card_ids.begin(); it != card_ids.end(); it++) {
        card = (Card *) storage.retrieve(*it);
        cards.push_back(card->repr());
    }

    data["id"] = deck.get_id();
    data["cards"] = cards;

    return data;
}