#include "../../include/core/game_engine.h"

#include <random>

namespace blackjack {
    
GameEngine::GameEngine(size_t player_balance) {
    //TODO add double down?
    deck_cards_ = {"As", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks",
                   "Ac", "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc",
                   "Ah", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh",
                   "Ad", "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd"};
    player_cards_.clear();
    dealer_cards_.clear();
    is_game_finished_ = true;
    player_balance_ = player_balance;
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

bool GameEngine::IsGameFinished() {
    return is_game_finished_;
}

size_t GameEngine::GetBalance() {
    return player_balance_;
}

const string& GameEngine::GetMessage() {
    return message_;
}

void blackjack::GameEngine::StartDeal(std::default_random_engine seed, size_t bet_size) {
    if (bet_size == 0 || bet_size > player_balance_) {
        throw std::invalid_argument("Invalid bet size");
    }
    current_bet_ = bet_size;
    is_game_finished_ = false;
    
    std::shuffle(deck_cards_.begin(), deck_cards_.end(), seed);

    //std::mt19937(std::random_device()()) random seed saved for later
    deck_.clear();
    
    //Shuffles vector with all cards and adds it to a deque
    std::shuffle(deck_cards_.begin(), deck_cards_.end(), seed);
    for (std::string card_info : deck_cards_) {
        deck_.push_back(card_info);
    }
    player_cards_.clear();
    dealer_cards_.clear();
    
    //Deals the first 2 cards each to the player and dealer, alternating, with the first dealer card being face down
    Deal(false, true);
    Deal(true, false);
    Deal(false, true);
    Deal(true, true);

    if (CalculateTotalValue(player_cards_) == kBlackjackValue) {
        is_game_finished_ = true;
        size_t win_amount = current_bet_ * kBlackjackPayMultiplier;
        message_ = kBlackjackString + std::to_string(win_amount);
        player_balance_ += win_amount;
    }
}

void GameEngine::Hit() {
    
    //Player shouldn't be able to hit without first calling StartDeal()
    if (player_cards_.empty()) {
        throw std::logic_error("Can't hit before start deal");
    }
    
    if (!is_game_finished_) {
        Deal(false, true);
    }

    //Checks bust
    if (CalculateTotalValue(player_cards_) > kBlackjackValue) {
        
        //Player balance shouldn't decrease by hitting after game is over
        if (!is_game_finished_) {
            message_ = kBustString + std::to_string(current_bet_);
            player_balance_ -= current_bet_;

        }
        is_game_finished_ = true;
    }
}

void GameEngine::Stand() {

    //Player shouldn't be able to stand without first calling StartDeal()
    if (player_cards_.empty()) {
        throw std::logic_error("Can't stand before start deal");
    }
    
    dealer_cards_[0].TurnOver();
    
    while (CalculateTotalValue(dealer_cards_) < kDealerStandValue) {
        Deal(true, true);
    }
    
    //Checks winner after dealer is done dealing cards to themselves
    size_t dealer_count = CalculateTotalValue(dealer_cards_);
    size_t player_count = CalculateTotalValue(player_cards_);

    //Player balance should only decrease first time game finished
    if (!is_game_finished_) {
        if (dealer_count > kBlackjackValue) {
            message_ = kDealerBustString + std::to_string(current_bet_);
            player_balance_ += current_bet_;
            
        } else if (dealer_count < player_count) {
            message_ = kWinString + std::to_string(current_bet_);
            player_balance_ += current_bet_;

        } else if (dealer_count > player_count) {
            message_ = kLoseString + std::to_string(current_bet_);
            player_balance_ -= current_bet_;
            
        } else {
            message_ = kPushString;
        }
    }
    is_game_finished_ = true;
}

size_t GameEngine::CalculateTotalValue(const vector<Card>& cards) {
    size_t total = 0;
    for (Card card : cards) {
        total += card.GetValue();
    }

    //Checks if the player is over 21 but has an ace
    if (total > kBlackjackValue) {
        for (Card card : cards) {
            if (card.GetName() == kAceString) {

                //Subtracts appropriate amount regardless if the Ace was an 11 or already a 1
                total -= card.GetValue();
                card.SoftAce();
                total += card.GetValue();

                //Only change one Ace if it brings the total under (in case there are more than one in a hand)
                if (total <= kBlackjackValue) {
                    break;
                }
            }
        }
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

void GameEngine::Reset(size_t balance) {
    player_cards_.clear();
    dealer_cards_.clear();
    player_balance_ = balance;
}

}


