#include <iostream>
#include "models/Player.hpp"

username_to_id_map Player::user_name_to_id;
std::string Player::name = "player";

Player::Player(std::string username, std::string password, std::string name) {
    this->_name = name;
    this->_username = username;
    this->_password = password;

    this->_playing_game = 0;
    // this is the model name
    name = "player";
}

std::string Player::get_name() {
    return this->_name;
}

std::string Player::get_username() {
    return this->_username;
}

void Player::set_name(std::string name) {
    this->_name = name;
}

std::string Player::get_password() {
    return this->_password;
}

void Player::set_password(std::string password) {
    this->_password = password;
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

bool Player::username_available(std::string username) {
    std::cout << "Checking if " << username << " is available" << std::endl;
    username_to_id_map::iterator it = Player::user_name_to_id.find(username);
    return it == Player::user_name_to_id.end();
}