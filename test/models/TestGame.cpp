#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../libs/doctest/doctest.h"
#include "../../include/models/Model.hpp"
#include "../../include/models/Deck.hpp"
#include "../../include/models/Game.hpp"

TEST_CASE("Checks if the game has the correct class name") {
    Game game(1, "1234");
    CHECK(game.get_class_name() == "game");
}

TEST_CASE ("Checks if the game has the correct creator") {
    Game game(1, "1234");
    CHECK(game.get_creator() == 1);
}

TEST_CASE ("Checks if the game has the correct access code") {
    Game game(1, "1234");
    CHECK(game.get_access_code() == "1234");
}

TEST_CASE ("Checks if the game has the correct access code after changing it") {
    Game game(1, "1234");
    game.set_access_code("4321");
    CHECK(game.get_access_code() == "4321");
}

TEST_CASE ("Checks if the game has the correct players") {
    Game game(1, "1234");
    game.add_player(1);
    game.add_player(2);
    game.add_player(3);

    unsigned_list & player_ids = game.get_player_ids();

    CHECK(player_ids.size() == 3);

    unsigned int player_id = player_ids.front();
    CHECK(player_id == 1);

    player_ids.pop_front();
    player_id = player_ids.front();

    CHECK(player_id == 2);

    player_ids.pop_front();
    player_id = player_ids.front();

    CHECK(player_id == 3);
}

TEST_CASE ("Checks if the game has the correct decks") {
    Game game(1, "1234");
    Deck deck1(new unsigned_list({1, 2, 3}));
    Deck deck2(new unsigned_list({4, 5, 6}));
    Deck deck3(new unsigned_list({7, 8, 9}));

    game.add_deck(deck1);
    game.add_deck(deck2);
    game.add_deck(deck3);

    unsigned_list & deck_ids = game.get_deck_ids();

    CHECK(deck_ids.size() == 3);

    unsigned int deck_id = deck_ids.front();
    CHECK(deck_id == deck1.get_id());

    deck_ids.pop_front();
    deck_id = deck_ids.front();

    CHECK(deck_id == deck2.get_id());

    deck_ids.pop_front();
    deck_id = deck_ids.front();

    CHECK(deck_id == deck3.get_id());
}

TEST_CASE ("Checks if the game has the correct cards") {
    Game game(1, "1234");
    Deck deck1(new unsigned_list({1, 2, 3}));
    Deck deck2(new unsigned_list({4, 5, 6}));
    Deck deck3(new unsigned_list({7, 8, 9}));

    game.add_deck(deck1);
    game.add_deck(deck2);
    game.add_deck(deck3);

    game.shuffle();

    unsigned_list & card_ids = game.get_card_ids();

    CHECK(card_ids.size() == 9);

    // because the list is shuffled, we can't know the order of the cards
    CHECK(std::find(card_ids.begin(), card_ids.end(), 1) != card_ids.end());
    CHECK(std::find(card_ids.begin(), card_ids.end(), 2) != card_ids.end());
    CHECK(std::find(card_ids.begin(), card_ids.end(), 3) != card_ids.end());
    CHECK(std::find(card_ids.begin(), card_ids.end(), 4) != card_ids.end());
    CHECK(std::find(card_ids.begin(), card_ids.end(), 5) != card_ids.end());
    CHECK(std::find(card_ids.begin(), card_ids.end(), 6) != card_ids.end());
    CHECK(std::find(card_ids.begin(), card_ids.end(), 7) != card_ids.end());
    CHECK(std::find(card_ids.begin(), card_ids.end(), 8) != card_ids.end());
    CHECK(std::find(card_ids.begin(), card_ids.end(), 9) != card_ids.end());
}

TEST_CASE ("Checks if the game deals the correct cards") {
    Game game(1, "1234");
    Deck deck1(new unsigned_list({3}));

    game.add_deck(deck1);

    game.shuffle();

    unsigned int card_id = game.deal_card();
    CHECK(card_id == 3);
}

TEST_CASE ("Checks if the game can shuffle a deck with only one card") {
    Game game(1, "1234");
    Deck deck1(new unsigned_list({3}));

    game.add_deck(deck1);

    game.shuffle();

    unsigned_list & card_ids = game.get_card_ids();

    CHECK(card_ids.size() == 1);
    CHECK(card_ids.front() == 3);
}

TEST_CASE ("Checks if the game can deal a card from a deck with only one card") {
    Game game(1, "1234");
    Deck deck1(new unsigned_list({3}));

    game.add_deck(deck1);

    game.shuffle();

    unsigned int card_id = game.deal_card();
    CHECK(card_id == 3);

    unsigned_list & card_ids = game.get_card_ids();

    CHECK(card_ids.size() == 0);
}

TEST_CASE ("Checks if the game can deal a card from a deck with no cards") {
    Game game(1, "1234");
    Deck deck1(new unsigned_list({}));

    game.add_deck(deck1);

    game.shuffle();

    unsigned int card_id = game.deal_card();
    CHECK(card_id == NO_CARD);

    unsigned_list & card_ids = game.get_card_ids();

    CHECK(card_ids.size() == 0);
}

TEST_CASE ("Checks if the game can shuffle the cards") {
    Game game(1, "1234");
    Deck deck1(new unsigned_list({1, 2, 3, 4, 5, 6, 7, 8, 9}));

    game.add_deck(deck1);

    game.shuffle();

    unsigned_list & card_ids = game.get_card_ids();

    CHECK(card_ids.size() == 9);

    // if the cards are shuffled, the order of the cards should be different
    unsigned_list::iterator it;
    std::string card_ids_str;

    for (it = card_ids.begin(); it != card_ids.end(); it++) {
        card_ids_str += std::to_string(*it);
    }

    // Is very unlikely that the cards are shuffled and the order is the same
    CHECK(card_ids_str != "123456789");
}