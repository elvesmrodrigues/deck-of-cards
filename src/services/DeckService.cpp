#include "services/DeckService.hpp"

namespace DeckService {
    void create(const httplib::Request &req, httplib::Response &res) {
        unsigned int deck_id = DeckFactory::create();

        json data;
        data["id"] = deck_id;

        res.status = HTTP_STATUS_CREATED;
        res.set_content(data.dump(), JSON_RESPONSE);
    }

    void remove(const httplib::Request &req, httplib::Response &res) {
        Storage & storage = Storage::get_instance();
        
        json data, data_res;

        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Deck::name, res, id))
            return;

        storage.remove(Deck::name, id);
        
        data_res["message"] = "Deck removed succesfully.";

        res.status = HTTP_STATUS_NO_CONTENT;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }

    void update(const httplib::Request &req, httplib::Response &res) {        
        json data;
        data["message"] = "Update a deck is not possible.";
        res.status = HTTP_STATUS_NOT_IMPLEMENTED;
        res.set_content(data.dump(), JSON_RESPONSE);
    }

    void retrieve(const httplib::Request &req, httplib::Response &res) {
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

    void retrieve_by_id(const httplib::Request &req, httplib::Response &res) {
        Storage &storage = Storage::get_instance();
        unsigned int id = Service::get_id_from_request(req);

        if (!Service::valid_id(Deck::name, res, id))
            return;

        Deck *deck = (Deck *) storage.retrieve(id);
        json data_res = DeckSerializer::serialize(* deck);

        res.status = HTTP_STATUS_OK;
        res.set_content(data_res.dump(), JSON_RESPONSE);
    }
}