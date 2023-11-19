#include "factories/PlayerFactory.hpp"

unsigned int PlayerFactory::create_player(const std::string name) {
    Storage &storage = Storage::get_instance();
    return storage.save(new Player(name));
}   