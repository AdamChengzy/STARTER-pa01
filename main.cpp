#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

int main(int argc, char* argv[]) {
    string tempSuit;
    string tempValue;
    bool gameOver = false;

    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream inFile1(argv[1]);
    ifstream inFile2(argv[2]);

    if (inFile1.fail() || inFile2.fail()) {
        cout << "Could not open file " << argv[2] << endl;
        return 1;
    }

    CardList aliceHand;
    CardList bobHand;

    while (inFile1 >> tempSuit >> tempValue) {
        aliceHand.insert(Card(tempSuit[0], tempValue));
    }
    inFile1.close();

    while (inFile2 >> tempSuit >> tempValue) {
        bobHand.insert(Card(tempSuit[0], tempValue));
    }
    inFile2.close();

    while (!gameOver) {
        bool bobMatched = false;
        bool aliceMatched = false;

        for (CardList::Iterator it = bobHand.rbegin(); it != bobHand.rend(); --it) {
            Card c = *it;
            if (aliceHand.contains(c)) {
                cout << "Bob picked matching card " << c << endl;
                aliceHand.remove(c);
                bobHand.remove(c);
                bobMatched = true;
                break;
            }
        }

        for (CardList::Iterator it = aliceHand.begin(); it != aliceHand.end(); ++it) {
            Card c = *it;
            if (bobHand.contains(c)) {
                cout << "Alice picked matching card " << c << endl;
                bobHand.remove(c);
                aliceHand.remove(c);
                aliceMatched = true;
                break;
            }
        }

        if (!aliceMatched && !bobMatched) {
            gameOver = true;
        }
    }

    cout << endl << "Bob's cards:" << endl;
    for (CardList::Iterator it = bobHand.begin(); it != bobHand.end(); ++it) {
        cout << *it << endl;
    }

    cout << endl << "Alice's cards:" << endl;
    for (CardList::Iterator it = aliceHand.begin(); it != aliceHand.end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}

