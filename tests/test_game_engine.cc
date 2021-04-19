#include <catch2/catch.hpp>
#include "../include/core/game_engine.h"

using namespace blackjack;

TEST_CASE("di") {
    GameEngine gameEngine;
    auto rng = std::default_random_engine {2};
    gameEngine.StartDeal(rng);
    REQUIRE(gameEngine.GetPlayerCards().size() == 2);
    REQUIRE(gameEngine.GetDealerCards()[0].GetName() == "A");
}
