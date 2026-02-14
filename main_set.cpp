#include <iostream>
#include <fstream>
#include <set>
#include "card.h"

void playSetGame(std::set<Card> &alice, std::set<Card> &bob) {
    bool matched = true;
    while(matched) {
        matched = false;
        // Alice forward
        for(auto it = alice.begin(); it != alice.end(); ++it) {
            if(bob.find(*it) != bob.end()) {
                std::cout << "Alice picked matching card " << *it << std::endl;
                bob.erase(*it);
                alice.erase(it);
                matched = true;
                break;
            }
        }
        if(!matched) break;
        // Bob reverse
        for(auto it = bob.rbegin(); it != bob.rend(); ++it) {
            if(alice.find(*it) != alice.end()) {
                std::cout << "Bob picked matching card " << *it << std::endl;
                alice.erase(*it);
                bob.erase(std::next(it).base()); // erase with reverse iterator
                matched = true;
                break;
            }
        }
    }

    std::cout << "\nAlice's cards:\n";
    for(const auto &c: alice) std::cout << c << std::endl;

    std::cout << "\nBob's cards:\n";
    for(const auto &c: bob) std::cout << c << std::endl;
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        std::cerr << "Provide two files!" << std::endl;
        return 1;
    }
    std::ifstream fa(argv[1]), fb(argv[2]);
    if(!fa || !fb) {
        std::cerr << "Cannot open files" << std::endl;
        return 1;
    }

    std::set<Card> alice, bob;
    char s; std::string v;
    while(fa >> s >> v) alice.insert(Card(s,v));
    while(fb >> s >> v) bob.insert(Card(s,v));

    playSetGame(alice, bob);
    return 0;
}

