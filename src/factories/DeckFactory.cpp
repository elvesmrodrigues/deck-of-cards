#include <iostream>
#include "factories/DeckFactory.hpp"

unsigned int DeckFactory::create() {
    Storage & storage = Storage::get_instance();

    std::vector<std::string> suits = {CARD_SUIT_HEARTS, CARD_SUIT_SPADES, CARD_SUIT_CLUBS, CARD_SUIT_DIAMONDS};
    std::vector<std::string> faces = {
                                CARD_FACE_ACE, CARD_FACE_2, CARD_FACE_3, CARD_FACE_4, CARD_FACE_5, CARD_FACE_6,
                                CARD_FACE_7, CARD_FACE_8, CARD_FACE_9, CARD_FACE_10, CARD_FACE_JACK, CARD_FACE_QUEEN, 
                                CARD_FACE_KING
                            };

    unsigned_list * card_ids = new unsigned_list();
    unsigned int i, j, card_id;

    for (i=0;i<suits.size();i++) {
        for(j=0;j<faces.size();j++) {
            card_id = storage.save(new Card(suits[i], faces[j]));
            card_ids->push_back(card_id); 
        }
    }

    return storage.save(new Deck(card_ids));
}