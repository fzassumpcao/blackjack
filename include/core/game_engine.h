#include <string>
#include <vector>
#include <deque>
#include <random>
#include "card.h"

using std::string;
using std::vector;

namespace blackjack{
    class GameEngine {
    public:
        GameEngine();
        
        /**
         * Shuffles the deck and deals 2 cards to the player and dealer.
         * @param seed seed for shuffling
         */
        void StartDeal(std::default_random_engine seed);
        
        /**
         * Deals one card to the player if they haven't busted and checks the game state after.
         */
        void Hit();
        void Stand();
        const vector<Card>& GetDealerCards();
        const vector<Card>& GetPlayerCards();
        std::deque<string> GetDeck();
        bool IsGameFinished();
        bool PlayerWon();
        
    private:
        vector<Card> dealer_cards_;
        vector<Card> player_cards_;
        bool player_win_;
        bool is_game_finished_;
        std::deque<string> deck_;
        vector<string> deck_cards_;
        
        const size_t kBlackjackValue = 21;
        const size_t kDealerStandValue = 17;

        /**
         * Helper method to calculate total value of a given list cards.
         * @param cards list of cards to sum value of
         * @return total value
         */
        size_t CalculateTotalValue(const vector<Card> cards);
        
        /**
         * Deals top card of the deck to the dealer or player either face up or face down 
         * and removes the card from the deck.
         * @param to_dealer true to deal to dealer, false to deal to player
         * @param face_up true to deal card face up or face down
         */
        void Deal(bool to_dealer, bool face_up);

    };
}
