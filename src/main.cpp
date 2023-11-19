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

    server.Get("/game", GameService::retrieve);
    server.Get("/game/:id", GameService::retrieve_by_id);
    server.Post("/game", GameService::create);
    server.Put("/game/:id", GameService::update);
    server.Delete("/game/:id", GameService::remove);
    server.Get("/game/:id/cards", GameService::count_cards_remaing_per_suit);
    server.Get("/game/:id/cards/detailed", GameService::count_cards_remaining);
    server.Get("/game/:id/shuffle", GameService::shuffle);
    server.Get("/game/:id/players", GameService::players);
    server.Put("/game/:id/players/add/:player_id", GameService::add_player);
    server.Get("/game/:id/players/:player_id/cards", GameService::player_cards);
    server.Put("/game/:id/players/:player_id/cards/deal", GameService::deal_card);
    server.Put("/game/:id/players/remove/:player_id", GameService::remove_player);
    server.Get("/game/:id/decks", GameService::decks);
    server.Put("/game/:id/decks/add/:deck_id", GameService::add_deck);

    server.listen("localhost", 8080);
}
