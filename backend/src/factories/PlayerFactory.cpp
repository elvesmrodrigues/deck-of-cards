#include "factories/PlayerFactory.hpp"

unsigned int PlayerFactory::create(const std::string name) {
    Storage &storage = Storage::get_instance();
    return storage.save(new Player(name));
}   