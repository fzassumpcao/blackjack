#include <catch2/catch.hpp>
#include <iostream>
#include "../include/core/game_engine.h"

using namespace blackjack;

TEST_CASE("Basic functionality") {
    GameEngine gameEngine(false);
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
    
    SECTION("Test hit") {
        gameEngine.Hit();
        REQUIRE(gameEngine.GetPlayerCards()[2].GetName() == "K");
        REQUIRE(gameEngine.GetPlayerCards()[2].GetSuit() == "h");
        REQUIRE(gameEngine.GetPlayerCards()[2].IsFaceUp() == true);
        REQUIRE_FALSE(gameEngine.IsGameFinished());
        
        gameEngine.Hit();
        REQUIRE(gameEngine.GetPlayerCards()[3].GetName() == "9");
        REQUIRE(gameEngine.GetPlayerCards()[3].GetSuit() == "c");
        REQUIRE(gameEngine.GetPlayerCards()[3].IsFaceUp() == true);
        
        //Player busts
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE_FALSE(gameEngine.PlayerWon());
        
        //Hitting when game is over shouldn't do anything
        gameEngine.Hit();
        REQUIRE(gameEngine.GetPlayerCards().size() == 4);
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE_FALSE(gameEngine.PlayerWon());
    }
    
    SECTION("Test stand, dealer with >= 17") {
        gameEngine.Stand();
        REQUIRE(gameEngine.GetDealerCards().size() == 2);
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE_FALSE(gameEngine.PlayerWon());
    }
    
    SECTION("Test stand, dealer with < 17 then bust") {
        
        //New seed to give dealer cards with value < 17
        auto rng1 = std::default_random_engine {2};
        gameEngine.StartDeal(rng1);
        REQUIRE(gameEngine.GetDealerCards()[0].GetValue() == 10);
        REQUIRE(gameEngine.GetDealerCards()[1].GetValue() == 2);
        REQUIRE(gameEngine.GetPlayerCards()[0].GetValue() == 3);
        REQUIRE(gameEngine.GetPlayerCards()[1].GetValue() == 3);
        
        gameEngine.Stand();  //Dealer should receive a 4, so 16 total, then 9 and bust
        REQUIRE(gameEngine.GetDealerCards().size() == 4);
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE(gameEngine.PlayerWon());
    }
    
    SECTION("Test start deal reset, multiple rounds") {
        gameEngine.Hit();
        gameEngine.Hit();
        gameEngine.Hit();
        gameEngine.Stand();
        gameEngine.Stand();
        gameEngine.StartDeal(rng);
        REQUIRE(gameEngine.GetPlayerCards().size() == 2);
        REQUIRE(gameEngine.GetDealerCards().size() == 2);
    }
    
    SECTION("Test stand, dealer < 17 and beats player") {
        
        //Same seed as before but the player hits to get the 4 and have a total of 10, 
        // then stand so dealer can get the 9 and get 21 to win
        auto rng1 = std::default_random_engine {2};
        gameEngine.StartDeal(rng1);
        gameEngine.Hit();
        gameEngine.Stand();
        
        REQUIRE(gameEngine.GetDealerCards()[2].GetValue() == 9);
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE_FALSE(gameEngine.PlayerWon());
    }
}

TEST_CASE("Test calculate value") {
    GameEngine gameEngine(false);
    vector<Card> cards;
    SECTION("No ace") {
        cards.push_back(Card("Kc", true));
        cards.push_back(Card("2s", true));
        cards.push_back(Card("Td", true));
        REQUIRE(gameEngine.CalculateTotalValue(cards) == 22);
    }
    
    SECTION("One ace, player not over 21") {
        cards.push_back(Card("Kc", true));
        cards.push_back(Card("As", true));
        REQUIRE(gameEngine.CalculateTotalValue(cards) == 21);
    }
    
    SECTION("One ace, player over 21") {
        cards.push_back(Card("Kc", true));
        cards.push_back(Card("2s", true));
        cards.push_back(Card("As", true));
        REQUIRE(gameEngine.CalculateTotalValue(cards) == 13);
    }
    
    SECTION("Two aces, only one soft") {
        cards.push_back(Card("Ac", true));
        cards.push_back(Card("2s", true));
        cards.push_back(Card("As", true));
        REQUIRE(gameEngine.CalculateTotalValue(cards) == 14);
    }
    
    SECTION("Two aces, both soft") {
        cards.push_back(Card("Kc", true));
        cards.push_back(Card("2s", true));
        cards.push_back(Card("As", true));
        cards.push_back(Card("Ad", true));
        REQUIRE(gameEngine.CalculateTotalValue(cards) == 14);
    }
}
