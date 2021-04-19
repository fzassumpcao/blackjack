#include <catch2/catch.hpp>
#include <iostream>
#include "../include/core/game_engine.h"

using namespace blackjack;

TEST_CASE("Basic functionality") {
    GameEngine gameEngine;
    auto rng = std::default_random_engine {0};
    //Top cards for seed: "2c", "9h", "8s", "Kd", "Kh", "9c", "5h", "Ts", "4d", "4s", "Tc", "3s", 
    // "As", "2h", "3h", "Qd", "Td", "8c", "2d", "5s", "7d",
    gameEngine.StartDeal(rng);
    vector<Card> player = gameEngine.GetPlayerCards();
    vector<Card> dealer = gameEngine.GetDealerCards();

    REQUIRE(player[0].GetName() == "2");
    REQUIRE(player[0].GetSuit() == "c");
    REQUIRE(player[0].IsFaceUp() == true);
    REQUIRE(player[1].GetName() == "8");
    REQUIRE(player[1].GetSuit() == "s");
    REQUIRE(player[1].IsFaceUp() == true);
    REQUIRE(dealer[0].GetName() == "9");
    REQUIRE(dealer[0].GetSuit() == "h");
    REQUIRE(dealer[0].IsFaceUp() == false);
    REQUIRE(dealer[1].GetName() == "K");
    REQUIRE(dealer[1].GetSuit() == "d");
    REQUIRE(dealer[1].IsFaceUp() == true);
    REQUIRE(gameEngine.GetDeck() == std::deque<string>());
    
    SECTION("Test hit") {
        
    }
}
