#include <cstddef>
#include <string>

using std::string;

namespace blackjack {
    
    class Card {
    public:
        Card(const string& info, bool is_face_up);
        const string& GetSuit() const;
        const string& GetName() const;
        size_t GetValue() const;
        bool IsFaceUp() const;
        void TurnOver();
        void SoftAce();

    private:
        string suit_;
        string name_;
        size_t value_;
        bool is_face_up_;
        
        const size_t kAceValue = 11;
        const size_t kSoftAceValue = 1;
        const size_t kFaceCardValue = 10;
        const char kAceChar = 'A';
        const char kKingChar = 'K';
        const char kQueenChar = 'Q';
        const char kJackChar = 'J';
        const char kTenChar = 'T';
        const char kDiamondChar = 'd';
        const char kHeartChar = 'h';
        const char kSpadeChar = 's';
        const char kClubChar = 'c';



        //TODO const for cards
    };

} //namespace blackjack