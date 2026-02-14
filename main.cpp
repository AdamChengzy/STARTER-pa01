// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 3) 
  {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream inFile1(argv[1]);
  ifstream inFile2(argv[2]);

  if (inFile1.fail() || inFile2.fail()) 
  {
    cout << "Could not open file " << argv[2] << endl;
    return 1;
  }

  set<Card> aliceHand;
  set<Card> bobHand;

  string tempCom;
  string tempValue;


  while (inFile1 >> tempCom >> tempValue) 
  {
    Card c(tempCom[0], tempValue);
    aliceHand.insert(c);
  }
  inFile1.close();


  while (inFile2 >> tempCom >> tempValue) 
  {
      Card c(tempCom[0], tempValue);
       bobHand.insert(c);
  }
  inFile2.close();


  while (true) {
    bool aliceMatched = false;
    bool bobMatched = false;

      for (set<Card>::iterator it = aliceHand.begin(); it != aliceHand.end(); ++it) 
      {
        Card currentCard = *it;
        if (bobHand.count(currentCard)) {
          cout << "Alice picked matching card " << currentCard << endl;
          bobHand.erase(currentCard);
          aliceHand.erase(it); 
                
          aliceMatched = true;
          break; 
        }
      }


      for (set<Card>::reverse_iterator it = bobHand.rbegin(); it != bobHand.rend(); ++it) 
      {
        Card currentCard = *it;
   
        if (aliceHand.count(currentCard)) 
        {
        cout << "Bob picked matching card " << currentCard << endl;
        aliceHand.erase(currentCard);
        bobHand.erase(currentCard);
        bobMatched = true;
        break; 
        }
      }


        if (!aliceMatched && !bobMatched) 
        {
          break;
        }
    }

    cout << endl << "Alice's cards:" << endl;
    for (set<Card>::iterator it = aliceHand.begin(); it != aliceHand.end(); ++it) 
    {
      cout << *it << endl;
    }

    cout << endl << "Bob's cards:" << endl;
    for (set<Card>::iterator it = bobHand.begin(); it != bobHand.end(); ++it) 
    {
      cout << *it << endl;
    }

    return 0;
}
