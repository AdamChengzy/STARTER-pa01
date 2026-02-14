#include <iostream>
#include "card.h"
#include "card_list.h"

static int fails = 0;
#define CHECK(cond) do { if(!(cond)) { ++fails; std::cout << "FAIL line " << __LINE__ << ": " #cond "\n"; } } while(0)

using namespace std;

int main() {

    CardBST tree;

    tree.insert(Card('c', '2'));
    tree.insert(Card('d', '5'));
    tree.insert(Card('h', 'A'));
    tree.insert(Card('s', '9'));
    tree.insert(Card('c', 'K'));

    cout << "Inorder traversal:" << endl;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        cout << *it << endl;
    }

    cout << endl;

    cout << "Reverse traversal:" << endl;
    auto it = tree.end();
    --it;
    while (true) {
        cout << *it << endl;
        if (it == tree.begin()) break;
        --it;
    }

    cout << endl;

    Card removeCard('d', '5');
    tree.remove(removeCard);

    cout << "After removal:" << endl;
    for (auto it2 = tree.begin(); it2 != tree.end(); ++it2) {
        cout << *it2 << endl;
    }

    return 0;
}
