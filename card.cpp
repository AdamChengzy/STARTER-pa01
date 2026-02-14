// card.cpp
// Author: Zhiyi cheng
// Implementation of the classes defined in card.h
#include "card.h"
#include <stdexcept>

Card::Card():m_suit(Suit::CLUBS), m_value(1) {}
Card::Card(Suit s, int v) : m_suit(s), m_value(v) {}

Card::Suit Card::suit() const {
    return m_suit;
}

int Card::value() const {
    return m_value;
}

    bool Card::operator==(const Card& o) const{
	    return m_suit == o.m_suit && m_value == o.m_value;
}

    bool Card::operator<(const Card& o) const{
	    if (m_suit != o.m_suit)
        return (int)m_suit < (int)o.m_suit;
    return m_value < o.m_value;
}
Card::Suit Card::suitFromChar(char c){
	Suit name;
	if (c=='c')
	{name=Suit::CLUBS;
	return name;}
	if (c=='d')
	{name=Suit::DIAMONDS;return name;}
	if (c=='s')
        {name=Suit::SPADES;return name;}
	if (c=='h')
	{name=Suit::HEARTS;return name;}
	throw std::runtime_error("Invalid suit char");}
	int Card::valueFromToken(const std::string& tok){
		if (tok == "a") return 1;
    if (tok == "j") return 11;
    if (tok == "q") return 12;
    if (tok == "k") return 13;

    int v = std::stoi(tok);
    if (v >= 2 && v <= 10) return v;

    throw std::runtime_error("Invalid value token");
}
	std::string valueToToken(int v){
	if (v == 1)  return "a";
    if (v == 11) return "j";
    if (v == 12) return "q";
    if (v == 13) return "k";
    return std::to_string(v);
}
std::ostream& operator<<(std::ostream& os, const Card& c) {
    char suitChar = '?';

    switch(c.suit()) {
        case Card::Suit::CLUBS:    suitChar = 'c'; break;
        case Card::Suit::DIAMONDS: suitChar = 'd'; break;
        case Card::Suit::SPADES:   suitChar = 's'; break;
        case Card::Suit::HEARTS:   suitChar = 'h'; break;
    }

    os << suitChar << " " << Card::valueToToken(c.value());
    return os;
}
std::string Card::valueToToken(int v) {
    return std::to_string(v);
}

