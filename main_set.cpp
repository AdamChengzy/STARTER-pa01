// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

static void printHand(const string& name, const set<Card>& hand) {
    cout << name << " cards:\n";
    for (const auto& c : hand) cout << c << "\n";
    cout << "\n";
}

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
set<Card> alice, bob;

    char s;
    string v;

    while (cardFile1 >> s >> v) {
        alice.insert(Card(Card::suitFromChar(s), Card::valueFromToken(v)));
    }

    while (cardFile2 >> s >> v) {
        bob.insert(Card(Card::suitFromChar(s), Card::valueFromToken(v)));
    }

    while (true) {
        bool found = false;

        for (auto it = alice.begin(); it != alice.end(); ++it) {
            auto jt = bob.find(*it);
            if (jt != bob.end()) {
                cout << "Alice picked matching card " << *it << "\n";
                bob.erase(jt);
                alice.erase(it);
                found = true;
                break;
            }
        }

        if (!found) break;

        found = false;

        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            auto jt = alice.find(*it);
            if (jt != alice.end()) {
                cout << "Bob picked matching card " << *it << "\n";
                alice.erase(jt);
                auto baseIt = it.base();
                --baseIt;
                bob.erase(baseIt);
                found = true;
                break;
            }
        }

        if (!found) break;
    }

    cout << "\n";
    printHand("Alice's", alice);
    printHand("Bob's", bob);
return 0;}
