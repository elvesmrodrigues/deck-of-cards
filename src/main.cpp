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

    std::cout << std::endl;
    std::cout << "Server up and running at http://localhost:8080..." << std::endl;
    std::cout << "Check the routes at https://github.com/elvesmrodrigues/deck-of-cards/tree/main#api" << std::endl;
    std::cout << "Press Ctrl+C to quit." << std::endl;
    std::cout << std::endl;

    server.listen("localhost", 8080);
}
