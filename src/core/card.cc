#include "../../include/core/card.h"

using std::string;

namespace blackjack {

Card::Card(const string &info, bool is_face_up) {
    if (info.length() != 2) {
        throw std::invalid_argument("Invalid info length");
    }

    char char1 = toupper(info.at(0));
    char char2 = tolower(info.at(1));

    if (isalpha(char1)) {
        if (char1 == 'A') {
            value_ = kAceValue;

        } else if (char1 == 'T' || char1 == 'J'
                   || char1 == 'Q' || char1 == 'K') {
            value_ = kFaceCardValue;

        } else {
            throw std::invalid_argument("Invalid first character");
        }

    } else {
        if (char1 == '1' || char1 == '0') {
            throw std::invalid_argument("First character cannot be 0 or 1");

        } else {

            //Subtracts the value in ASCII of char1 from that of 0 (48) to convert to the proper integer
            value_ = char1 - '0';
        }
    }

    name_ = char1;

    if (char2 == 'c' || char2 == 'd'
        || char2 == 'h' || char2 == 's') {
        suit_ = char2;

    } else {
        throw std::invalid_argument("Invalid suit");
    }
    is_face_up_ = is_face_up;
}

const string &Card::GetSuit() const {
    return suit_;
}

const string &Card::GetName() const {
    return name_;
}

size_t Card::GetValue() const {
    return value_;
}

bool Card::IsFaceUp() const {
    return is_face_up_;
}

void Card::TurnOver() {
    is_face_up_ = true;
}

void Card::SoftAce() {
    if (name_ != "A") {
        throw std::logic_error("Card isn't an ace");
    }
    value_ = kSoftAceValue;
}
}




