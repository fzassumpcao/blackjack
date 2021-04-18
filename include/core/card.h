#include <cstddef>
#include <string>

using std::string;

namespace blackjack {
    
    class Card {
    public:
        Card(const string& info, bool is_face_up);
        const string& GetSuit();
        const string& GetName();
        size_t GetValue();
        void TurnOver();

    private:
        string suit_;
        string name_;
        size_t value_;
        bool is_face_up_;
        
        const size_t kAceValue = 11;
        const size_t kFaceCardValue = 10;
    };

} //namespace blackjack