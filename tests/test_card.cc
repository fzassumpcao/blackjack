#include <catch2/catch.hpp>
#include "../include/core/card.h"

using namespace blackjack;

TEST_CASE("Invalid card info") {
    SECTION("Invalid length") {
        REQUIRE_THROWS_AS(Card("A", true), std::invalid_argument);
        REQUIRE_THROWS_AS(Card("Aca", true), std::invalid_argument);
    }
    SECTION("Invalid first letter") {
        REQUIRE_THROWS_AS(Card("Ec", true), std::invalid_argument);
    }
    SECTION("Invalid first number") {
        REQUIRE_THROWS_AS(Card("0c", true), std::invalid_argument);
        REQUIRE_THROWS_AS(Card("1c", true), std::invalid_argument);
    }
    SECTION("Invalid suit") {
        REQUIRE_THROWS_AS(Card("3e", true), std::invalid_argument);
        REQUIRE_THROWS_AS(Card("K8", true), std::invalid_argument);
    }
}

TEST_CASE("Test number cards") {
    SECTION("3, lowercase suit") {
        Card card("3c", true);
        REQUIRE(card.GetSuit() == "c");
        REQUIRE(card.GetName() == "3");
        REQUIRE(card.GetValue() == 3);
    }
    SECTION("9, uppercase suit") {
        Card card("9H", true);
        REQUIRE(card.GetSuit() == "h");
        REQUIRE(card.GetName() == "9");
        REQUIRE(card.GetValue() == 9);
    }
}

TEST_CASE("Test face cards") {
    SECTION("T lowercase, lowercase suit") {
        Card card("ts", true);
        REQUIRE(card.GetSuit() == "s");
        REQUIRE(card.GetName() == "T");
        REQUIRE(card.GetValue() == 10);
    }
    SECTION("J lowercase, uppercase suit") {
        Card card("jD", true);
        REQUIRE(card.GetSuit() == "d");
        REQUIRE(card.GetName() == "J");
        REQUIRE(card.GetValue() == 10);
    }
    SECTION("Q uppercase, lowercase suit") {
        Card card("Qc", true);
        REQUIRE(card.GetSuit() == "c");
        REQUIRE(card.GetName() == "Q");
        REQUIRE(card.GetValue() == 10);
    }
    SECTION("K uppercase, uppercase suit") {
        Card card("KH", true);
        REQUIRE(card.GetSuit() == "h");
        REQUIRE(card.GetName() == "K");
        REQUIRE(card.GetValue() == 10);
    }
}

TEST_CASE("Test ace") {
    SECTION("Lowercase A") {
        Card card("ac", true);
        REQUIRE(card.GetSuit() == "c");
        REQUIRE(card.GetName() == "A");
        REQUIRE(card.GetValue() == 11);
        
    }
    SECTION("Uppercase A") {
        Card card("AS", true);
        REQUIRE(card.GetSuit() == "s");
        REQUIRE(card.GetName() == "A");
        REQUIRE(card.GetValue() == 11);
    }
}

TEST_CASE("Test face up/down and turn over") {
    SECTION("Card face down, turn over") {
        Card card("ac", false);
        REQUIRE_FALSE(card.IsFaceUp());
        card.TurnOver();
        REQUIRE(card.IsFaceUp());
    }
    SECTION("Card face up, turn over") {
        Card card("ac", true);
        REQUIRE(card.IsFaceUp());
        card.TurnOver();
        REQUIRE(card.IsFaceUp());
    }
}

TEST_CASE("Test soft ace functionality") {
    SECTION("Card not an ace") {
        Card card("8c", true);
        REQUIRE_THROWS_AS(card.SoftAce(), std::logic_error);
    }
    SECTION("Card is an ace") {
        Card card("ac", true);
        card.SoftAce();
        REQUIRE(card.GetValue() == 1);
        
        //Shouldn't change anything
        card.SoftAce();
        REQUIRE(card.GetValue() == 1);
    }
}
