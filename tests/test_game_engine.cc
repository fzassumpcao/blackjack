#include <catch2/catch.hpp>
#include <iostream>
#include "../include/core/game_engine.h"

using namespace blackjack;

TEST_CASE("Basic functionality") {
    GameEngine gameEngine(1000);
    auto rng = std::default_random_engine {0};
    //Top cards for seed: "2c", "9h", "8s", "Kd", "Kh", "9c", "5h", "Ts", "4d", "4s", "Tc", "3s", 
    // "As", "2h", "3h", "Qd", "Td", "8c", "2d", "5s", "7d",
    gameEngine.StartDeal(rng, 100);
    vector<Card> player = gameEngine.GetPlayerCards();
    vector<Card> dealer = gameEngine.GetDealerCards();

    REQUIRE(player[0].GetName() == "5");
    REQUIRE(player[0].GetSuit() == "s");
    REQUIRE(player[0].IsFaceUp() == true);
    REQUIRE(player[1].GetName() == "2");
    REQUIRE(player[1].GetSuit() == "c");
    REQUIRE(player[1].IsFaceUp() == true);
    REQUIRE(dealer[0].GetName() == "3");
    REQUIRE(dealer[0].GetSuit() == "d");
    REQUIRE(dealer[0].IsFaceUp() == false);
    REQUIRE(dealer[1].GetName() == "6");
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
        REQUIRE(gameEngine.GetPlayerCards()[3].GetSuit() == "s");
        REQUIRE(gameEngine.GetPlayerCards()[3].IsFaceUp() == true);
        
        //Player busts, subtracts bet from balance
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE(gameEngine.GetMessage() == "Bust! You lost 100");
        REQUIRE(gameEngine.GetBalance() == 900);
        
        //Hitting when game is over shouldn't do anything
        gameEngine.Hit();
        REQUIRE(gameEngine.GetPlayerCards().size() == 4);
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE(gameEngine.GetMessage() == "Bust! You lost 100");
        REQUIRE(gameEngine.GetBalance() == 900);
    }
    
    SECTION("Test stand, dealer stand with < 17 and wins") {
        gameEngine.Stand();
        REQUIRE(gameEngine.GetDealerCards().size() == 3);
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE(gameEngine.GetMessage() == "You lost 100");
        REQUIRE(gameEngine.GetBalance() == 900);
    }
    
    SECTION("Test stand, dealer with < 17 then bust") {
        
        //New seed to give dealer cards with value < 17
        auto rng1 = std::default_random_engine {2};
        gameEngine.StartDeal(rng1, 100);
        REQUIRE(gameEngine.GetDealerCards()[0].GetValue() == 2);
        REQUIRE(gameEngine.GetDealerCards()[1].GetValue() == 10);
        REQUIRE(gameEngine.GetPlayerCards()[0].GetValue() == 8);
        REQUIRE(gameEngine.GetPlayerCards()[1].GetValue() == 10);
        
        gameEngine.Stand();  //Dealer should receive a 4, so 16 total, then 9 and bust
        REQUIRE(gameEngine.GetDealerCards().size() == 4);
        REQUIRE(gameEngine.IsGameFinished());
        REQUIRE(gameEngine.GetMessage() == "Dealer bust! You won 100");
        REQUIRE(gameEngine.GetBalance() == 1100);

    }
    
    SECTION("Test start deal reset, multiple rounds") {
        gameEngine.Hit();
        gameEngine.Hit();
        gameEngine.Hit();
        gameEngine.Stand();
        gameEngine.Stand();
        gameEngine.StartDeal(rng, 100);
        REQUIRE(gameEngine.GetPlayerCards().size() == 2);
        REQUIRE(gameEngine.GetDealerCards().size() == 2);
    }
    
    SECTION("Test reset") {
        gameEngine.Stand();
        gameEngine.Reset(1);
        REQUIRE(gameEngine.GetPlayerCards().size() == 0);
        REQUIRE(gameEngine.GetDealerCards().size() == 0);   
        REQUIRE(gameEngine.GetBalance() == 1);
        REQUIRE_FALSE(gameEngine.IsGameFinished());
    }
}

TEST_CASE("Test calculate value") {
    GameEngine gameEngine(1000);
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

TEST_CASE("Invalid commands") {
    GameEngine gameEngine(10);
    auto rng = std::default_random_engine {0};
    SECTION("Hit before start deal") {
        REQUIRE_THROWS_AS(gameEngine.Hit(), std::logic_error);
    }
    SECTION("Stand before start deal") {
        REQUIRE_THROWS_AS(gameEngine.Stand(), std::logic_error);
    }
    SECTION("Bet size greater than balance") {
        REQUIRE_THROWS_AS(gameEngine.StartDeal(rng, 11), std::invalid_argument);
    }
    SECTION("Bet size 0") {
        REQUIRE_THROWS_AS(gameEngine.StartDeal(rng, 0), std::invalid_argument);
    }
}
