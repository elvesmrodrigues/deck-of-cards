#include "models/Game.hpp"

std::string Game::name = "game";

Game::Game(unsigned int creator_id, std::string access_code) {
    this->_creator_id = creator_id;
    this->_access_code = access_code;

    std::srand(static_cast<unsigned int>(std::time(0)));
    
    name = "game";
}

void Game::add_player(unsigned int player_id) {
    this->_player_ids.push_front(player_id);
}

void Game::remove_player(unsigned int player_id) {
    this->_player_ids.remove(player_id);
}

void Game::add_deck(Deck &deck) {
    this->_deck_ids.push_front(deck.get_id());
    this->_card_ids.splice(this->_card_ids.end(), deck.get_card_ids());
    this->shuffle();
}

void Game::shuffle() {
    if (this->_card_ids.size() <= 1)
        return;

    int n_cards = this->_card_ids.size();

    // pointers to elements of the list that will have their positions swapped
    int offset_1, offset_2;    
    unsigned_list::iterator it1, it2;

    for (int i=0;i<n_cards;i++) {
        offset_1 = std::rand() % n_cards;
        offset_2 = std::rand() % n_cards;

        if (offset_1 == offset_2)
            continue;

        it1 = offset_1 != 0 ? std::next(this->_card_ids.begin(), offset_1) : this->_card_ids.begin();
        it2 = offset_2 != 0 ? std::next(this->_card_ids.begin(), offset_2) : this->_card_ids.begin();

        std::iter_swap(it1, it2);
     }

}

unsigned int Game::deal_card() {
    if (!this->_card_ids.size())
        return NO_CARD;

    unsigned int chosen_card = this->_card_ids.front();
    this->_card_ids.pop_front();
    
    return chosen_card;
}

unsigned int Game::get_creator() {
    return this->_creator_id;
}

unsigned_list & Game::get_card_ids() {
    return this->_card_ids;
}

std::string Game::get_class_name() {
    return name;
}

std::string Game::get_access_code() {
    return this->_access_code;
}

void Game::set_access_code(std::string access_code) {
    this->_access_code = access_code;
}

unsigned_list & Game::get_player_ids() {
    return this->_player_ids;
}

unsigned_list & Game::get_deck_ids() {
    return this->_deck_ids;
}
