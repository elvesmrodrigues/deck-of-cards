#include "models/Deck.hpp"
std::string Deck::name = "deck";

Deck::Deck(unsigned_list * card_ids) {
    this->_card_ids = card_ids;
    name = "deck";
}

unsigned_list Deck::get_card_ids() {
    return * this->_card_ids;
}

Deck::~Deck() {
    delete this->_card_ids;
}

std::string Deck::get_class_name() {
    return name;
}

Deck::~Deck() {
    // nothing to do here, since the destructor of the Storage class will delete the cards
}