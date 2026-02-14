#include <iostream>
#include <cassert>
#include "card_list.h"

void testInsertContains() {
    CardBST bst;
    Card c1('c',"a"), c2('h',"k");
    bst.insert(c1); bst.insert(c2);
    assert(bst.contains(c1)); assert(bst.contains(c2));
    assert(!bst.contains(Card('d',"5")));
}

void testRemove() {
    CardBST bst;
    Card c1('c',"a"), c2('h',"k");
    bst.insert(c1); bst.insert(c2);
    bst.remove(c1); assert(!bst.contains(c1));
    bst.remove(c2); assert(!bst.contains(c2));
}

void testIterator() {
    CardBST bst;
    bst.insert(Card('c',"a")); bst.insert(Card('d',"2")); bst.insert(Card('h',"k"));
    std::string s;
    for(auto it=bst.begin(); it!=bst.end(); ++it) s += (*it).value;
    assert(s=="a2k");
}

void testPlayGame() {
    CardBST alice, bob;
    alice.insert(Card('c',"a")); alice.insert(Card('h',"k"));
    bob.insert(Card('h',"k")); bob.insert(Card('s',"2"));
    playGame(alice,bob);
}

int main() {
    testInsertContains();
    testRemove();
    testIterator();
    testPlayGame();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

