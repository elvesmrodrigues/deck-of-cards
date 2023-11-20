#include "models/AuthToken.hpp"

std::string AuthToken::name = "auth_token";

AuthToken::AuthToken(unsigned int player_id) {
    this->_player_id = player_id;
}

unsigned int AuthToken::get_player_id() {
    return this->_player_id;
}

std::string AuthToken::get_class_name() {
    return AuthToken::name;
}
