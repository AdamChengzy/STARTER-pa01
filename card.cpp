// card.cpp
// Author: Zhiyi Cheng
// Implementation of the classes defined in card.h

#include "card.h"

Card::Card() {
    suit = 'c';
    value = 0;
}

Card::Card(char s, string v) {
    suit = s;
    
    if (v == "a") {
        value = 1;
    }
    else if (v == "j") {
        value = 11;
    }
    else if (v == "q") {
        value = 12;
    }
    else if (v == "k") {
        value = 13;
    }
    else {
        value = stoi(v);
    }
}

char Card::getSuit() const {
    return suit;
}

int Card::getValue() const {
    return value;
}


int Card::getSuitRank() const {
    if (suit == 'c') return 1;
    if (suit == 'd') return 2;
    if (suit == 's') return 3;
    if (suit == 'h') return 4;
    return 0;
}

// 核心比较逻辑：重载 <
bool Card::operator<(const Card& other) const {

    if (getSuitRank() != other.getSuitRank()) {
        return getSuitRank() < other.getSuitRank();
    }
    return value < other.value;
}

bool Card::operator>(const Card& other) const {
    return other < *this; 
}

bool Card::operator==(const Card& other) const {
    return (suit == other.suit) && (value == other.value);
}

bool Card::operator!=(const Card& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& os, const Card& c) {
    os << c.suit << " "; 

    if (c.value == 1) os << "a";
    else if (c.value == 11) os << "j";
    else if (c.value == 12) os << "q";
    else if (c.value == 13) os << "k";
    else os << c.value;
    return os;
}
