#include "models/Player.hpp"

std::string Player::name = "player";

Player::Player(std::string name) {
    this->_name = name;
    this->_playing_game = 0;
    // this is the model name
    name = "player";
}

std::string Player::get_name() {
    return this->_name;
}

void Player::set_name(std::string name) {
    this->_name = name;
}

unsigned_list &Player::get_card_ids() {
    return this->_card_ids;
}

void Player::receive_card(unsigned int card_id) {
    this->_card_ids.push_back(card_id);
}

std::string Player::get_class_name() {
    return name;
}

bool Player::is_playing() {
    return this->_playing_game != NO_PLAYING;
}

void Player::enter_game(unsigned int game_id) {
    this->_playing_game = game_id;
    this->_card_ids.clear();
}

unsigned int Player::get_game_playing() {
    return this->_playing_game;
}

void Player::leave_game() {
    this->_playing_game = NO_PLAYING;
}