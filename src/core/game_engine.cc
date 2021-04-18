#include "../../include/core/game_engine.h"
#include <random>

using namespace blackjack;
GameEngine::GameEngine() {
    
}

void blackjack::GameEngine::StartDeal() {
    deck_.clear();
    std::shuffle(kDeckCards.begin(), kDeckCards.end(), std::mt19937(std::random_device()()));
    for (std::string card_info : kDeckCards) {
        deck_.push_back(card_info);
    }
    player_cards_.clear();
    dealer_cards_.clear();
    player_cards_.push_back(Card(deck_.front(), true));
    deck_.pop_front();
    dealer_cards_.push_back(Card(deck_.front(), false));
    deck_.pop_front();
    player_cards_.push_back(Card(deck_.front(), true));
    deck_.pop_front();
    dealer_cards_.push_back(Card(deck_.front(), true));
    deck_.pop_front();
    
    if (CalculateTotalValue(player_cards_) == kBlackjackVaLue) {
        //TODO
    } 
}

void GameEngine::Hit() {
    player_cards_.push_back(Card(deck_.front(), true));
    deck_.pop_front();}

void GameEngine::Stand() {
    dealer_cards_[1].TurnOver();
    
    while (CalculateTotalValue(dealer_cards_) < kDealerStandValue) {
        de
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



