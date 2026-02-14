// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

using namespace std;

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

  CardBST alice;
  CardBST bob;

  char s;
string v;

while (cardFile1 >> s >> v) {
    alice.insert(Card(
        Card::suitFromChar(s),
        Card::valueFromToken(v)
    ));
}

while (cardFile2 >> s >> v) {
    bob.insert(Card(
        Card::suitFromChar(s),
        Card::valueFromToken(v)
    ));
}
  playGame(alice, bob, cout);


 cout << "\nAlice's cards:\n";
  alice.printInOrder(cout);
  cout << "\nBob's cards:\n";
  bob.printInOrder(cout);
  
  return 0;
}
