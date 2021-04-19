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
        void StartDeal(std::default_random_engine seed);
        void Hit();
        void Stand();
        const vector<Card>& GetDealerCards() const;
        const vector<Card>& GetPlayerCards() const;
        std::deque<string> GetDeck();
        
    private:
        vector<Card> dealer_cards_;
        vector<Card> player_cards_;
        std::deque<string> deck_;
        
        vector<string> deck_cards_ = {"As","2s","3s","4s","5s","6s","7s","8s","9s","Ts","Js","Qs","Ks",
                                      "Ac","2c","3c","4c","5c","6c","7c","8c","9c","Tc","Jc","Qc","Kc",
                                      "Ah","2h","3h","4h","5h","6h","7h","8h","9h","Th","Jh","Qh","Kh",
                                      "Ad","2d","3d","4d","5d","6d","7d","8d","9d","Td","Jd","Qd","Kd",};
        
        const size_t kBlackjackVaLue = 21;
        const size_t kDealerStandValue = 17;

        size_t CalculateTotalValue(const vector<Card> cards);
        void Deal(bool to_dealer, bool face_up);

    };
}
