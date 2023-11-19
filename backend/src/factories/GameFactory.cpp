#include "factories/GameFactory.hpp"

unsigned int GameFactory::create_game(const int creator_id) {
    Storage &storage = Storage::get_instance();
    return storage.save(new Game(creator_id));
}