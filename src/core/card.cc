#include "../../include/core/card.h"

using std::string;
using namespace blackjack;

Card::Card(const string& info, bool is_face_up) {
    if (info.size() != 2) {
        throw new std::invalid_argument("Invalid info length");
    }
    
    char char1 = info.at(0);
    char char2 = tolower(info.at(1));
    
    if (isalpha(char1)) {
        if (char1 == 'A') {
            value_ = kAceValue;
            
        } else if (toupper(char1) == 'T' || toupper(char1) == 'J' 
        || toupper(char1) == 'Q' || toupper(char1) == 'K') {
            value_ = kFaceCardValue;
            
        } else {
            throw new std::invalid_argument("Invalid first character");
        }
        
    } else {
        if (char1 == '1' || char1 == '0') {
            throw new std::invalid_argument("First character cannot be 0 or 1");
            
        } else {
            value_ = char1;
        }
    }
    
    name_ = info.at(0);

    if (toupper(char2) == 'C' || toupper(char2) == 'D' 
    || toupper(char2) == 'H' || toupper(char2) == 'S') {
        suit_ = char2;
        
    } else {
        throw new std::invalid_argument("Invalid suit");
    }
    is_face_up_ = is_face_up;
}

const string &Card::GetSuit() {
    return suit_;
}

const string &Card::GetName() {
    return name_;
}

size_t Card::GetValue() {
    return value_;
}

void Card::TurnOver() {
    is_face_up_ = true;
}



