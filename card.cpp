#include "card.h"

// Helper arrays to order suits and values
static const std::string suits = "cdsh"; // clubs, diamonds, spades, hearts
static const std::string values = "a234567891jqk"; // '10' handled separately

int suitOrder(char s) {
    switch(s) {
        case 'c': return 0;
        case 'd': return 1;
        case 's': return 2;
        case 'h': return 3;
    }
    return -1;
}

int valueOrder(const std::string &v) {
    if(v == "a") return 0;
    if(v == "j") return 11;
    if(v == "q") return 12;
    if(v == "k") return 13;
    if(v == "10") return 10;
    return std::stoi(v);
}

bool Card::operator==(const Card &other) const {
    return suit == other.suit && value == other.value;
}

bool Card::operator<(const Card &other) const {
    if(suitOrder(suit) != suitOrder(other.suit))
        return suitOrder(suit) < suitOrder(other.suit);
    return valueOrder(value) < valueOrder(other.value);
}

bool Card::operator>(const Card &other) const {
    return other < *this;
}

std::ostream& operator<<(std::ostream &os, const Card &c) {
    os << c.suit << " " << c.value;
    return os;
}

