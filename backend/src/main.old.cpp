#include <iostream>
#include <string>


#include "../libs/server/httplib.h"
#include "../libs/nlohmann/json.hpp"

using json = nlohmann::json;

void handle_index(const httplib::Request &req, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
}

void handle_game(const httplib::Request &req, httplib::Response &res) {
    res.set_content("Game Page", "text/plain");
}

void handle_get_game(const httplib::Request &req, httplib::Response &res) {
    const std::string game_id = req.path_params.at("id");

    std::cout << "The game id is: " << game_id << std::endl;
    res.set_content(game_id, "text/plain");
}

void handle_create_game(const httplib::Request &req, httplib::Response &res) {
    try {
        json data = json::parse(req.body);
        res.status = 200;
        res.set_content(data.dump(), "application/json");
    } catch (const json::parse_error &e) {
        res.status = 400;
        res.set_content("Bad Request: Invalid JSON format!", "text/plain");
    }

}

void handle_game_update(const httplib::Request &req, httplib::Response &res) {

}

void handle_game_delete(const httplib::Request &req, httplib::Response &res) {
    const std::string game_id = req.path_params.at("id");

    std::cout << "Deleting game: " << game_id << std::endl;

    res.status = 201;
    res.set_content("{\"message\": \"Game deleted!\"}", "application/json");
}

int main(int argc, char const *argv[]) {
    httplib::Server server;

    server.Get("/", handle_index);
    server.Get("/game", handle_game);
    server.Get("/game/:id", handle_get_game);
    server.Post("/game", handle_create_game);
    server.Delete("/game/:id", handle_game_delete);

    server.listen("localhost", 8080);
}
