#include "serializers/GameSerializer.hpp"

json GameSerializer::serialize(Game &game) {
    json data;

    Storage & storage = Storage::get_instance();

    std::list<unsigned int> card_ids = game.get_card_ids();
    std::list<unsigned int>::iterator it;

    Card * card;
    std::list<std::string> cards;
    for (it = card_ids.begin(); it != card_ids.end(); it++) {
        card = (Card *) storage.retrieve(*it);
        cards.push_back(card->repr());
    }

    data["id"] = game.get_id();
    data["creator"] = game.get_creator();
    data["players"] = game.get_player_ids();
    data["num_remaining_cards"] = card_ids.size();
    data["cards"] = cards;
    data["num_decks"] = game.get_deck_ids().size();

    return data;
} 