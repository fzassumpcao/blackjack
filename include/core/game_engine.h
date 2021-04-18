#include <string>
#include <vector>
#include "card.h"

using std::string;
using std::vector;

namespace blackjack{
    class GameEngine {
    public:
        GameEngine();
        void Shuffle();
        
        
    private:
        vector<Card> dealer_cards_;
        vector<Card> player_cards_;
        const vector<string> kDeck = {"As","1s","2s","3s","4s","5s","6s","7s","8s","9s","Ts","Js","Qs","Ks",
                                      "Ac","1c","2c","3c","4c","5c","6c","7c","8c","9c","Tc","Jc","Qc","Kc",
                                      "Ah","1h","2h","3h","4h","5h","6h","7h","8h","9h","Th","Jh","Qh","Kh",
                                      "Ad","1d","2d","3d","4d","5d","6d","7d","8d","9d","Td","Jd","Qd","Kd",};
    };
}
