#include "../../include/core/game_engine.h"
#include <random>

using namespace blackjack;
GameEngine::GameEngine() {
    
}

const vector<Card> &GameEngine::GetDealerCards() const {
    return dealer_cards_;
}

const vector<Card> &GameEngine::GetPlayerCards() const {
    return player_cards_;
}

std::deque<string> GameEngine::GetDeck() {
    return deck_;
}


void blackjack::GameEngine::StartDeal(std::default_random_engine seed) {
    //std::mt19937(std::random_device()()) random seed saved for later
    deck_.clear();
    std::shuffle(deck_cards_.begin(), deck_cards_.end(), seed);
    for (std::string card_info : deck_cards_) {
        deck_.push_back(card_info);
    }
    player_cards_.clear();
    dealer_cards_.clear();
    Deal(false, true);
    Deal(true, false);
    Deal(false, true);
    Deal(true, true);
    
    if (CalculateTotalValue(player_cards_) == kBlackjackVaLue) {
        //TODO
    } 
}

void GameEngine::Hit() {
    Deal(false, true);
}

void GameEngine::Stand() {
    dealer_cards_[1].TurnOver();
    
    while (CalculateTotalValue(dealer_cards_) < kDealerStandValue) {
        Deal(true, true);
    }
}

size_t GameEngine::CalculateTotalValue(const vector<Card> cards) {
    size_t total = 0;
    for (Card card : cards) {
        total += card.GetValue();
    }
    return total;
}

void GameEngine::Deal(bool to_dealer, bool face_up) {
    if (to_dealer) {
        dealer_cards_.push_back(Card(deck_.front(), face_up));
        
    } else {
        player_cards_.push_back(Card(deck_.front(), face_up));
    }
    deck_.pop_front();
}


