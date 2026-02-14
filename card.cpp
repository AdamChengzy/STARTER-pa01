// card.cpp
// Author: Zhiyi Cheng
// Implementation of the classes defined in card.h

#include "card.h"

bool Card::operator<(const Card& other) const {

    if (getComRank() != other.getComRank()) {
        return getComRank() < other.getComRank();
    }
    return value < other.value;
}

bool Card::operator>(const Card& other) const {
    return other < *this; 
}

bool Card::operator==(const Card& other) const {
    return (com == other.com) && (value == other.value);
}

bool Card::operator!=(const Card& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& os, const Card& c) {
    os << c.com << " "; 

    if (c.value == 1) os << "a";
    else if (c.value == 11) os << "j";
    else if (c.value == 12) os << "q";
    else if (c.value == 13) os << "k";
    else os << c.value;
    return os;
}

char Card::getCom() const {
    return com;
}

int Card::getComRank() const {
    if (com == 'c') return 1;
    if (com == 'd') return 2;
    if (com == 's') return 3;
    if (com == 'h') return 4;
    return 0;
}

int Card::getValue() const {
    return value;
}

Card::Card() {
    com = 'c';
    value = 0;
}

Card::Card(char c, string v) {
    com = c;
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

