#include "factories/PlayerFactory.hpp"

unsigned int PlayerFactory::create(const std::string username, const std::string password, const std::string name) {
    Storage &storage = Storage::get_instance();    
    unsigned int player_id = storage.save(new Player(username, password, name));

    return player_id;
}   