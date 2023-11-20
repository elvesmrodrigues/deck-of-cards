#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../libs/doctest/doctest.h"

#include "../../include/models/Model.hpp"
#include "../../include/models/Player.hpp"

TEST_CASE("Checks if the Model has the correct class name") {
    Model * model = new Player("johndoe", "123456", "John Doe");

    CHECK(model->get_class_name() == "player");
}

TEST_CASE("Checks if the player model has the correct attributes") {
    Player * player = new Player("johndoe", "123456", "John Doe");

    CHECK(player->get_username() == "johndoe");
    CHECK(player->get_password() == "123456");
    CHECK(player->get_name() == "John Doe");
}

TEST_CASE("Checks if the player model can enter a game") {
    Player * player = new Player("johndoe", "123456", "John Doe");

    player->enter_game(1);

    CHECK(player->is_playing());
    CHECK(player->get_game_playing() == 1);
}

TEST_CASE("Checks if the player model can leave a game") {
    Player * player = new Player("johndoe", "123456", "John Doe");

    player->enter_game(1);
    player->leave_game();

    CHECK(!player->is_playing());
    CHECK(player->get_game_playing() == 0);
}

TEST_CASE("Checks if the player model can receive a card") {
    Player * player = new Player("johndoe", "123456", "John Doe");

    player->receive_card(1);
    player->receive_card(2);
    player->receive_card(3);

    unsigned_list & card_ids = player->get_card_ids();

    CHECK(card_ids.size() == 3);

    unsigned int card_id = card_ids.front();
    CHECK(card_id == 1);

    card_ids.pop_front();
    card_id = card_ids.front();

    CHECK(card_id == 2);

    card_ids.pop_front();
    card_id = card_ids.front();

    CHECK(card_id == 3);

    delete player;
}

TEST_CASE("Checks if the player model can add a username") {
    Player player("johndoe", "123456", "John Doe");
    player.set_id(1);

    CHECK(!Player::username_available("johndoe"));
}

TEST_CASE("Checks if a username is available after deleting it") {
    Player player("alice", "123456", "John Doe");

    player.set_id(3);

    CHECK(!Player::username_available("alice"));

    Player::remove_username("alice");

    CHECK(Player::username_available("alice"));
}