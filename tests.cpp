#include <iostream>
#include <sstream>
#include <cassert>
#include "card.h"
#include "card_list.h" // CardBST 和 playGame 的头文件

using namespace std;

// ============================
// BST Insert Tests
// ============================
void testInsertEmpty() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    assert(bst.contains(Card('H', "2")));
}

void testInsertSingleNode() {
    CardBST bst;
    bst.insert(Card('S', "A"));
    assert(bst.contains(Card('S', "A")));
}

void testInsertMultipleNodes() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    bst.insert(Card('C', "3"));
    bst.insert(Card('D', "4"));
    assert(bst.contains(Card('H', "2")));
    assert(bst.contains(Card('C', "3")));
    assert(bst.contains(Card('D', "4")));
}

void testInsertDuplicate() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    bst.insert(Card('H', "2")); // duplicate
    int count = 0;
    for (auto it = bst.begin(); it != bst.end(); ++it) count++;
    assert(count == 1);
}

void testInsertEdgeCards() {
    CardBST bst;
    bst.insert(Card('C', "2"));
    bst.insert(Card('S', "A"));
    assert(bst.contains(Card('C', "2")));
    assert(bst.contains(Card('S', "A")));
}

// ============================
// BST Remove Tests
// ============================
void testRemoveLeaf() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    bst.remove(Card('H', "2"));
    assert(!bst.contains(Card('H', "2")));
}

void testRemoveNonExistent() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    bst.remove(Card('D', "5")); // doesn't exist
    assert(bst.contains(Card('H', "2")));
}

void testRemoveRootWithOneChild() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    bst.insert(Card('C', "3"));
    bst.remove(Card('H', "2"));
    assert(!bst.contains(Card('H', "2")));
    assert(bst.contains(Card('C', "3")));
}

void testRemoveRootWithTwoChildren() {
    CardBST bst;
    bst.insert(Card('H', "3"));
    bst.insert(Card('C', "2"));
    bst.insert(Card('D', "4"));
    bst.remove(Card('H', "3"));
    assert(!bst.contains(Card('H', "3")));
    assert(bst.contains(Card('C', "2")));
    assert(bst.contains(Card('D', "4")));
}

void testRemoveEmptyTree() {
    CardBST bst;
    bst.remove(Card('H', "2")); // should not crash
    assert(!bst.contains(Card('H', "2")));
}

// ============================
// Iterator Tests
// ============================
void testIteratorEmpty() {
    CardBST bst;
    assert(bst.begin() == bst.end());
    assert(bst.rbegin() == bst.rend());
}

void testIteratorSingleNode() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    auto it = bst.begin();
    assert(*it == Card('H', "2"));
    ++it;
    assert(it == bst.end());
}

void testIteratorMultipleNodes() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    bst.insert(Card('C', "3"));
    bst.insert(Card('D', "4"));

    vector<Card> expected = {Card('H',"2"), Card('C',"3"), Card('D',"4")};
    auto it = bst.begin();
    for (auto& c : expected) {
        assert(*it == c);
        ++it;
    }
}

void testReverseIterator() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    bst.insert(Card('C', "3"));
    bst.insert(Card('D', "4"));

    vector<Card> expected = {Card('D',"4"), Card('C',"3"), Card('H',"2")};
    auto rit = bst.rbegin();
    for (auto& c : expected) {
        assert(*rit == c);
        ++rit;
    }
}

void testIteratorComparison() {
    CardBST bst;
    bst.insert(Card('H', "2"));
    auto it1 = bst.begin();
    auto it2 = bst.begin();
    assert(it1 == it2);
    ++it2;
    assert(it1 != it2);
}

// ============================
// playGame Tests
// ============================
void testPlayGameCommonCards() {
    CardBST alice, bob;
    alice.insert(Card('H', "2"));
    alice.insert(Card('C', "3"));
    bob.insert(Card('H', "2"));
    bob.insert(Card('D', "4"));

    stringstream ss;
    playGame(alice, bob, ss);
    string output = ss.str();
    assert(output.find("Alice picked matching card H2") != string::npos ||
           output.find("Bob picked matching card H2") != string::npos);
    // matched card should be removed
    assert(!alice.contains(Card('H', "2")));
    assert(!bob.contains(Card('H', "2")));
}

void testPlayGameOneEmptyHand() {
    CardBST alice, bob;
    alice.insert(Card('H', "2"));
    // Bob empty
    stringstream ss;
    playGame(alice, bob, ss);
    string output = ss.str();
    // Alice can't match, output should not contain "picked matching card"
    assert(output.find("picked matching card") == string::npos);
    assert(alice.contains(Card('H', "2")));
}

void testPlayGameNoCommonCards() {
    CardBST alice, bob;
    alice.insert(Card('H', "2"));
    bob.insert(Card('D', "4"));

    stringstream ss;
    playGame(alice, bob, ss);
    string output = ss.str();
    // No matches, output empty
    assert(output.find("picked matching card") == string::npos);
    // cards still remain
    assert(alice.contains(Card('H', "2")));
    assert(bob.contains(Card('D', "4")));
}

// ============================
// Main
// ============================
int main() {
    cout << "Running BST insert tests..." << endl;
    testInsertEmpty();
    testInsertSingleNode();
    testInsertMultipleNodes();
    testInsertDuplicate();
    testInsertEdgeCards();
    cout << "BST insert tests passed." << endl;

    cout << "Running BST remove tests..." << endl;
    testRemoveLeaf();
    testRemoveNonExistent();
    testRemoveRootWithOneChild();
    testRemoveRootWithTwoChildren();
    testRemoveEmptyTree();
    cout << "BST remove tests passed." << endl;

    cout << "Running iterator tests..." << endl;
    testIteratorEmpty();
    testIteratorSingleNode();
    testIteratorMultipleNodes();
    testReverseIterator();
    testIteratorComparison();
    cout << "Iterator tests passed." << endl;

    cout << "Running playGame tests..." << endl;
    testPlayGameCommonCards();
    testPlayGameOneEmptyHand();
    testPlayGameNoCommonCards();
    cout << "playGame tests passed." << endl;

    cout << "All tests passed!" << endl;
    return 0;
}

