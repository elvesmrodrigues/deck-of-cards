#include <iostream>

#include <list>
#include <string>

#include "../libs/server/httplib.h"

#include "models/Model.hpp"
#include "models/Card.hpp"
#include "models/Deck.hpp"
#include "models/Player.hpp"
#include "models/Game.hpp"

#include "factories/DeckFactory.hpp"
#include "factories/PlayerFactory.hpp"
#include "factories/GameFactory.hpp"

#include "services/DeckService.hpp"
#include "services/PlayerService.hpp"
#include "services/GameService.hpp"
#include "services/Service.hpp"

#include "storages/Storage.hpp"

int main(int argc, char const *argv[]) {
    httplib::Server server;
    
    server.Get("/deck", DeckService::retrieve);
    server.Get("/deck/:id", DeckService::retrieve_by_id);
    server.Post("/deck", DeckService::create);
    server.Put("/deck/:id", DeckService::update);
    server.Delete("/deck/:id", DeckService::remove);

    server.Get("/player", PlayerService::retrieve);
    server.Get("/player/:id", PlayerService::retrieve_by_id);
    server.Post("/player", PlayerService::create);
    server.Put("/player/:id", PlayerService::update);
    server.Delete("/player/:id", PlayerService::remove);

    server.listen("localhost", 8080);
}
