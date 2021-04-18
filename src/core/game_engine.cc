#include "../../include/core/game_engine.h"

void blackjack::GameEngine::Shuffle() {
    std::random_shuffle(kDeck.begin(), kDeck.end());
}

blackjack::GameEngine::GameEngine() {

}

