#include "factories/GameFactory.hpp"

unsigned int GameFactory::create(const int creator_id, std::string access_code) {
    Storage &storage = Storage::get_instance();
    return storage.save(new Game(creator_id, access_code));
}