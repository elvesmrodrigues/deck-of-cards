#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../libs/doctest/doctest.h"
#include "../../include/models/Model.hpp"
#include "../../include/models/Card.hpp"
#include "../../include/models/Player.hpp"
#include "../../include/models/Game.hpp"
#include "../../include/storages/Storage.hpp"

TEST_CASE("Checks if the Storage class is a singleton") {
    Storage & storage = Storage::get_instance();

    CHECK(&storage == &Storage::get_instance());
}

TEST_CASE("Checks if the Storage class can save a model") {
    Storage & storage = Storage::get_instance();
    Card * card = new Card(CARD_SUIT_CLUBS, CARD_FACE_10);

    unsigned int id = storage.save(card);

    Card * retrieved_card = (Card *) storage.retrieve(id);    

    CHECK(retrieved_card->get_suit() == CARD_SUIT_CLUBS);
    CHECK(retrieved_card->get_face() == CARD_FACE_10);
}

TEST_CASE("Checks if the Storage class can update a model") {
    Storage & storage = Storage::get_instance();
    Player * player = new Player("johndoe", "123456", "John Doe");

    unsigned int id = storage.save(player);

    Player * retrieved_player = (Player *) storage.retrieve(id);

    CHECK(retrieved_player->get_username() == "johndoe");

    retrieved_player->set_name("John Doe Jr.");
    storage.update(id, retrieved_player);

    Player * updated_player = (Player *) storage.retrieve(id);

    CHECK(updated_player->get_name() == "John Doe Jr.");
}

TEST_CASE("Checks if the Storage class can retrieve a model") {
    Storage & storage = Storage::get_instance();
    Card * card = new Card(CARD_SUIT_CLUBS, CARD_FACE_10);

    unsigned int id = storage.save(card);

    Card * retrieved_card = (Card *) storage.retrieve(id);    

    CHECK(retrieved_card->get_suit() == CARD_SUIT_CLUBS);
    CHECK(retrieved_card->get_face() == CARD_FACE_10);
}

TEST_CASE("Checks if the Storage class can batch retrieve models") {
    Storage & storage = Storage::get_instance();

    Card * card1 = new Card(CARD_SUIT_CLUBS, CARD_FACE_10);
    Card * card2 = new Card(CARD_SUIT_SPADES, CARD_FACE_2);
    Card * card3 = new Card(CARD_SUIT_HEARTS, CARD_FACE_3);

    unsigned int id1 = storage.save(card1);
    unsigned int id2 = storage.save(card2);
    unsigned int id3 = storage.save(card3);

    unsigned_list ids = {id1, id2, id3};

    model_list retrieved_cards = storage.batch_retrieve(ids);

    CHECK(retrieved_cards.size() == 3);

    Card * retrieved_card = (Card *) retrieved_cards.front();
    CHECK(retrieved_card->get_suit() == CARD_SUIT_CLUBS);

    retrieved_cards.pop_front();
    retrieved_card = (Card *) retrieved_cards.front();
    CHECK(retrieved_card->get_suit() == CARD_SUIT_SPADES);

    retrieved_cards.pop_front();

    retrieved_card = (Card *) retrieved_cards.front();
    CHECK(retrieved_card->get_suit() == CARD_SUIT_HEARTS);
}

TEST_CASE("Checks if the Storage class can retrieve all models of a type") {
    Storage & storage = Storage::get_instance();

    Game * game1 = new Game(1, "12345");
    Game * game2 = new Game(2, "1df345");
    Game * game3 = new Game(3, "12sd5");

    unsigned int id1 = storage.save(game1);
    unsigned int id2 = storage.save(game2);
    unsigned int id3 = storage.save(game3);

    unsigned_list ids = {id1, id2, id3};

    model_list retrieved_cards = storage.retrieve_all(Game::name);

    CHECK(retrieved_cards.size() == 3);

    Game * retrieved_game = (Game *) retrieved_cards.front();
    CHECK(retrieved_game->get_access_code() == "12345");

    retrieved_cards.pop_front();

    retrieved_game = (Game *) retrieved_cards.front();
    CHECK(retrieved_game->get_access_code() == "1df345");

    retrieved_cards.pop_front();

    retrieved_game = (Game *) retrieved_cards.front();
    CHECK(retrieved_game->get_access_code() == "12sd5");
}

TEST_CASE("Checks if the Storage class can remove a model") {
    Storage & storage = Storage::get_instance();
    Card * card = new Card(CARD_SUIT_CLUBS, CARD_FACE_10);

    unsigned int id = storage.save(card);

    Card * retrieved_card = (Card *) storage.retrieve(id);    

    CHECK(retrieved_card->get_suit() == CARD_SUIT_CLUBS);
    CHECK(retrieved_card->get_face() == CARD_FACE_10);

    storage.remove(Card::name, id);

    CHECK(storage.exists(Card::name, id) == false);
}

TEST_CASE("Checks if the Storage class can check if a model exists") {
    Storage & storage = Storage::get_instance();
    Card * card = new Card(CARD_SUIT_CLUBS, CARD_FACE_10);

    unsigned int id = storage.save(card);

    CHECK(storage.exists(Card::name, id) == true);
}