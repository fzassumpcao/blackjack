#include <random>
#include <deque>
#include <chrono>
#include <thread>
#include "card.h"

using std::string;
using std::vector;

namespace blackjack{
    class GameEngine {
    public:
        GameEngine(size_t player_balance);
        
        /**
         * Shuffles the deck and deals 2 cards to the player and dealer.
         * @param seed seed for shuffling
         */
        void StartDeal(std::default_random_engine seed, size_t bet_size);  //Tried making the parameter const & but would get errors from <random>
        
        /**
         * Deals one card to the player if they haven't busted and updates game state.
         */
        void Hit();
        
        /**
         * Deals card to the dealer until their total is >= 17 and updates game state.
         */
        void Stand();

        /**
         * Helper method to calculate total value of a given list cards.
         * @param cards list of cards to sum value of
         * @return total value
         */
        size_t CalculateTotalValue(const vector<Card>& cards);
        
        /**
         * Resets variables and sets new player balance
         * @param balance new balance
         */
        void Reset(size_t balance);
        
        const vector<Card>& GetDealerCards();
        const vector<Card>& GetPlayerCards();
        bool IsGameFinished();
        size_t GetBalance();
        const string& GetMessage();
        
    private:
        vector<Card> dealer_cards_;
        vector<Card> player_cards_;
        bool is_game_finished_;
        std::deque<string> deck_;
        vector<string> deck_cards_;
        size_t player_balance_;
        size_t current_bet_;
        string message_;
        
        const size_t kBlackjackValue = 21;
        const size_t kDealerStandValue = 17;
        const string kAceString = "A";
        const string kBustString = "Bust! You lost ";
        const string kBlackjackString = "Blackjack! You won ";
        const string kDealerBustString = "Dealer bust! You won ";
        const string kWinString = "You won ";
        const string kLoseString = "You lost ";
        const string kPushString = "Push!";
        const float kBlackjackPayMultiplier = 1.5;
        
        /**
         * Deals top card of the deck to the dealer or player either face up or face down 
         * and removes the card from the deck.
         * @param to_dealer true to deal to dealer, false to deal to player
         * @param face_up true to deal card face up or face down
         */
        void Deal(bool to_dealer, bool face_up);
    };
}
