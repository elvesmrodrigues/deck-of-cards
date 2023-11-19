#include "models/Deck.hpp"
std::string Deck::name = "deck";

Deck::Deck(std::list<unsigned int> * card_ids) {
    this->_card_ids = card_ids;
    name = "deck";
}

std::list<unsigned int> Deck::get_card_ids() {
    return * this->_card_ids;
}

Deck::~Deck() {
    delete this->_card_ids;
}

std::string Deck::get_class_name() {
    return name;
}