#include "card_list.h"
#include <iostream>

// Private helpers
CardBST::Node* CardBST::find(const Card &c) const {
    Node *n = root;
    while(n) {
        if(c == n->data) return n;
        else if(c < n->data) n = n->left;
        else n = n->right;
    }
    return nullptr;
}

CardBST::Node* CardBST::minimum(Node *n) const {
    while(n && n->left) n = n->left;
    return n;
}

CardBST::Node* CardBST::maximum(Node *n) const {
    while(n && n->right) n = n->right;
    return n;
}

CardBST::Node* CardBST::successor(Node *n) const {
    if(n->right) return minimum(n->right);
    Node *p = n->parent;
    while(p && n == p->right) { n = p; p = p->parent; }
    return p;
}

CardBST::Node* CardBST::predecessor(Node *n) const {
    if(n->left) return maximum(n->left);
    Node *p = n->parent;
    while(p && n == p->left) { n = p; p = p->parent; }
    return p;
}

void CardBST::transplant(Node *u, Node *v) {
    if(u->parent == nullptr) root = v;
    else if(u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if(v) v->parent = u->parent;
}

void CardBST::destroy(Node *n) {
    if(!n) return;
    destroy(n->left);
    destroy(n->right);
    delete n;
}

// Public methods
void CardBST::insert(const Card &c) {
    Node *y = nullptr;
    Node *x = root;
    Node *z = new Node(c);
    while(x) { y = x; x = (c < x->data) ? x->left : x->right; }
    z->parent = y;
    if(!y) root = z;
    else if(c < y->data) y->left = z;
    else y->right = z;
}

void CardBST::remove(const Card &c) {
    Node *z = find(c);
    if(!z) return;
    if(!z->left) transplant(z, z->right);
    else if(!z->right) transplant(z, z->left);
    else {
        Node *y = minimum(z->right);
        if(y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    delete z;
}

bool CardBST::contains(const Card &c) const { return find(c) != nullptr; }

void CardBST::print() const { inorderPrint(root); std::cout << std::endl; }

void CardBST::inorderPrint(Node *n) const {
    if(!n) return;
    inorderPrint(n->left);
    std::cout << n->data << std::endl;
    inorderPrint(n->right);
}

// Iterator
CardBST::Iterator& CardBST::Iterator::operator++() {
    current = tree->successor(current);
    return *this;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
    if(!current) current = tree->maximum(tree->root);
    else current = tree->predecessor(current);
    return *this;
}

CardBST::Iterator CardBST::begin() const { return Iterator(minimum(root), this); }
CardBST::Iterator CardBST::end() const { return Iterator(nullptr, this); }
CardBST::Iterator CardBST::rbegin() const { return Iterator(maximum(root), this); }
CardBST::Iterator CardBST::rend() const { return Iterator(nullptr, this); }

// Game logic
void playGame(CardBST &alice, CardBST &bob) {
    bool matched = true;
    while(matched) {
        matched = false;
        // Alice forward
        for(auto it = alice.begin(); it != alice.end(); ++it) {
            if(bob.contains(*it)) {
                std::cout << "Alice picked matching card " << *it << std::endl;
                bob.remove(*it);
                alice.remove(*it);
                matched = true;
                break;
            }
        }
        if(!matched) break;
        // Bob reverse
        for(auto it = bob.rbegin(); it != bob.rend(); --it) {
            if(alice.contains(*it)) {
                std::cout << "Bob picked matching card " << *it << std::endl;
                alice.remove(*it);
                bob.remove(*it);
                matched = true;
                break;
            }
        }
    }

    std::cout << "\nAlice's cards:\n"; alice.print();
    std::cout << "\nBob's cards:\n"; bob.print();
}

