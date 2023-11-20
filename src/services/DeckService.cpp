#include "services/DeckService.hpp"

namespace DeckService {
    void auth_create(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int deck_id = DeckFactory::create();

        json data;
        data["id"] = deck_id;

        res.status = HTTP_STATUS_CREATED;
        res.set_content(data.dump(), JSON_RESPONSE);
    }

    void auth_remove(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Deck::name, res, id))
            return;

        json data_res;

        data_res["message"] = "A deck, once created, cannot be deleted.";

        res.status = HTTP_STATUS_METHOD_NOT_ALLOWED;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_update(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {        
        json data_res;

        data_res["message"] = "Update a deck is not possible.";

        res.status = HTTP_STATUS_METHOD_NOT_ALLOWED;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_retrieve(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        Storage & storage = Storage::get_instance();

        model_list decks = storage.retrieve_all(Deck::name);

        if (!decks.size()) {
            res.status = HTTP_STATUS_OK;
            res.set_content("[]", JSON_RESPONSE);
            return;
        }

        model_list::iterator it;

        Deck *deck;
        json_list parsed_decks;
        
        for (it = decks.begin(); it != decks.end(); it++) {
            json data;

            deck = (Deck *) *it;

            parsed_decks.push_back(DeckSerializer::serialize(* deck));
        }

        json data_res(parsed_decks);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void auth_retrieve_by_id(const httplib::Request &req, httplib::Response &res, const Player & logged_player) {
        Storage &storage = Storage::get_instance();
        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Deck::name, res, id))
            return;

        Deck *deck = (Deck *) storage.retrieve(id);

        json data_res = DeckSerializer::serialize(* deck);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void add_routes(httplib::Server & server) {
        server.Get("/decks", [](const httplib::Request &req, httplib::Response & res){ 
            AuthMiddleware::verify_request(req, res, DeckService::auth_retrieve); 
        });

        server.Get("/decks/:id", [](const httplib::Request &req, httplib::Response & res){ 
            AuthMiddleware::verify_request(req, res, DeckService::auth_retrieve_by_id); 
        });
        
        server.Post("/decks", [](const httplib::Request &req, httplib::Response & res){ 
            AuthMiddleware::verify_request(req, res, DeckService::auth_create); 
        });

        server.Put("/decks/:id", [](const httplib::Request &req, httplib::Response & res){ 
            AuthMiddleware::verify_request(req, res, DeckService::auth_update); 
        });    

        server.Delete("/decks/:id", [](const httplib::Request &req, httplib::Response & res){ 
            AuthMiddleware::verify_request(req, res, DeckService::auth_remove); 
        });
    }
}