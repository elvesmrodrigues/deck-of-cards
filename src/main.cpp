#include <iostream>

#include "../libs/server/httplib.h"

#include "services/AuthService.hpp"
#include "services/DeckService.hpp"
#include "services/PlayerService.hpp"
#include "services/GameService.hpp"
#include "services/Service.hpp"

int main(int argc, char const *argv[]) {
    httplib::Server server;

    AuthService::add_routes(server);
    DeckService::add_routes(server);
    PlayerService::add_routes(server);
    GameService::add_routes(server);

    server.listen("localhost", 8080);
}
