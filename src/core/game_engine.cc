#include "../../include/core/game_engine.h"
#include <random>

using namespace blackjack;
GameEngine::GameEngine() {
    deck_cards_ = {"As","2s","3s","4s","5s","6s","7s","8s","9s","Ts","Js","Qs","Ks",
                   "Ac","2c","3c","4c","5c","6c","7c","8c","9c","Tc","Jc","Qc","Kc",
                   "Ah","2h","3h","4h","5h","6h","7h","8h","9h","Th","Jh","Qh","Kh",
                   "Ad","2d","3d","4d","5d","6d","7d","8d","9d","Td","Jd","Qd","Kd"};
    player_cards_.clear();
    dealer_cards_.clear();
    player_win_ = false;
    is_game_finished_ = false;
}

const vector<Card> &GameEngine::GetDealerCards() {
    return dealer_cards_;
}

const vector<Card> &GameEngine::GetPlayerCards() {
    return player_cards_;
}

std::deque<string> GameEngine::GetDeck() {
    return deck_;
}


void blackjack::GameEngine::StartDeal(std::default_random_engine seed) {
    player_win_ = false;
    is_game_finished_ = false;
    
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
        is_game_finished_ = true;
        player_win_ = true;
        //TODO method to
    } 
}

void GameEngine::Hit() {
    if (!is_game_finished_) {
        Deal(false, true);
    }
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


