#include "models/Card.hpp"

std::string Card::name = "card";

void Card::_calculate_value() {
    if (this->_face == CARD_FACE_ACE)
        this->_value = 1;

    else if (this->_face == CARD_FACE_JACK)
        this->_value = 11;

    else if (this->_face == CARD_FACE_QUEEN)
        this->_value = 12;

    else if (this->_face == CARD_FACE_KING)
        this->_value = 13;

    else
        this->_value = std::stoi(this->_face);
}

Card::Card(std::string suit, std::string face) {
    this->_suit = suit; 
    this->_face = face;

    this->_calculate_value();
}

std::string Card::get_suit() {
    return this->_suit;
}

std::string Card::get_face() {
    return this->_face;
}

int Card::get_value() {
    return this->_value;
}

std::string Card::get_class_name() {
    return name;
}

std::string Card::repr() {
    return this->_suit + " " + this->_face;
}