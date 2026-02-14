// card_list.cpp
// Author: Zhiyi Cheng
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>

using namespace std;

CardBST::CardBST() {
    root = nullptr;
}

CardBST::~CardBST() {
    clear(root);
}

void CardBST::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

bool CardBST::insert(const Card& c) {
    if (!root) {
        root = new Node(c);
        return true;
    }

    Node* cur = root;
    Node* parent = nullptr;

    while (cur) {
        parent = cur;
        if (c == cur->key) return false;
        if (c < cur->key) cur = cur->left;
        else cur = cur->right;
    }

    Node* n = new Node(c);
    n->parent = parent;

    if (c < parent->key) parent->left = n;
    else parent->right = n;

    return true;
}

bool CardBST::contains(const Card& c) const {
    Node* cur = root;
    while (cur) {
        if (c == cur->key) return true;
        if (c < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return false;
}

CardBST::Node* CardBST::findNode(const Card& c) const {
    Node* cur = root;
    while (cur) {
        if (c == cur->key) return cur;
        if (c < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return nullptr;
}

CardBST::Node* CardBST::minimum(Node* n) const {
    if (!n) return nullptr;
    while (n->left) n = n->left;
    return n;
}

CardBST::Node* CardBST::maximum(Node* n) const {
    if (!n) return nullptr;
    while (n->right) n = n->right;
    return n;
}

CardBST::Node* CardBST::successor(Node* n) const {
    if (!n) return nullptr;
    if (n->right) return minimum(n->right);

    Node* p = n->parent;
    while (p && n == p->right) {
        n = p;
        p = p->parent;
    }
    return p;
}

CardBST::Node* CardBST::predecessor(Node* n) const {
    if (!n) return nullptr;
    if (n->left) return maximum(n->left);

    Node* p = n->parent;
    while (p && n == p->left) {
        n = p;
        p = p->parent;
    }
    return p;
}

void CardBST::transplant(Node* u, Node* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    if (v) v->parent = u->parent;
}

bool CardBST::remove(const Card& c) {
    Node* n = findNode(c);
    if (!n) return false;

    if (!n->left && !n->right) {
        transplant(n, nullptr);
    }
    else if (!n->left) {
        transplant(n, n->right);
    }
    else if (!n->right) {
        transplant(n, n->left);
    }
    else {
        Node* s = minimum(n->right);
        if (s->parent != n) {
            transplant(s, s->right);
            s->right = n->right;
            if (s->right) s->right->parent = s;
        }
        transplant(n, s);
        s->left = n->left;
        if (s->left) s->left->parent = s;
    }

    delete n;
    return true;
}

CardBST::Iterator::Iterator(Node* n, const CardBST* t) {
    node = n;
    tree = t;
}

const Card& CardBST::Iterator::operator*() const {
    return node->key;
}

CardBST::Iterator& CardBST::Iterator::operator++() {
    node = tree->successor(node);
    return *this;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
    node = tree->predecessor(node);
    return *this;
}

bool CardBST::Iterator::operator!=(const Iterator& other) const {
    return node != other.node;
}

CardBST::Iterator CardBST::begin() const {
    return Iterator(minimum(root), this);
}

CardBST::Iterator CardBST::end() const {
    return Iterator(nullptr, this);
}

CardBST::Iterator CardBST::rbegin() const {
    return Iterator(maximum(root), this);
}

CardBST::Iterator CardBST::rend() const {
    return Iterator(nullptr, this);
}

void playGame(CardBST& alice, CardBST& bob) {
    while (true) {

        bool found = false;

        for (auto it = alice.begin(); it != alice.end(); ++it) {
            Card c = *it;
            if (bob.contains(c)) {
                cout << "Alice picked matching card " << c << endl;
                alice.remove(c);
                bob.remove(c);
                found = true;
                break;
            }
        }

        if (!found) break;

        found = false;

        for (auto it = bob.rbegin(); it != bob.rend(); --it) {
            Card c = *it;
            if (alice.contains(c)) {
                cout << "Bob picked matching card " << c << endl;
                bob.remove(c);
                alice.remove(c);
                found = true;
                break;
            }
        }

        if (!found) break;
    }
}

