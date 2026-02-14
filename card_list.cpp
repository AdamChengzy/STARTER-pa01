// card_list.cpp
// Author: Zhiyi Cheng
// Implementation of the classes defined in card_list.h

#include "card_list.h"

CardList::CardList() {
    root = nullptr;
}
CardList::~CardList() {
    clear(root);
}

void CardList::clear(Node* n) {
    if (n != nullptr) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

void CardList::insert(Card c) {
    if (root == nullptr) {
        root = new Node(c);
        return;
    }

    Node* curr = root;
    Node* prev = nullptr;

    while (curr != nullptr) {
        prev = curr;
        if (c < curr->info) {
            curr = curr->left;
        } else if (c > curr->info) {
            curr = curr->right;
        } else {
            return;
        }
    }

    Node* newNode = new Node(c);
    newNode->parent = prev; 

    if (c < prev->info) {
        prev->left = newNode;
    } else {
        prev->right = newNode;
    }
}

bool CardList::contains(Card c) const {
    Node* curr = root;
    while (curr != nullptr) {
        if (c == curr->info) {
            return true;
        }
        if (c < curr->info) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return false;
}

CardList::Node* CardList::getMax(Node* n) const {
    if (n == nullptr) return nullptr;
    while (n->right != nullptr) {
        n = n->right;
    }
    return n;
}

CardList::Node* CardList::getMin(Node* n) const {
    if (n == nullptr) return nullptr;
    while (n->left != nullptr) {
        n = n->left;
    }
    return n;
}

CardList::Node* CardList::getSuccessor(Node* n) const {
    if (n == nullptr) return nullptr;

    if (n->right != nullptr) {
        return getMin(n->right);
    }

    Node* p = n->parent;
    while (p != nullptr && n == p->right) {
        n = p;
        p = p->parent;
    }
    return p;
}

CardList::Node* CardList::getPredecessor(Node* n) const {
    if (n == nullptr) return nullptr;
    if (n->left != nullptr) {
        return getMax(n->left);
    }
    Node* p = n->parent;
    while (p != nullptr && n == p->left) {
        n = p;
        p = p->parent;
    }
    return p;
}

void CardList::remove(Card c) {
    if (root == nullptr) return;

    Node* curr = root;
    while (curr != nullptr) {
        if (c == curr->info) break;
        if (c < curr->info) curr = curr->left;
        else curr = curr->right;
    }

    if (curr == nullptr) return; 

    if (curr->left == nullptr && curr->right == nullptr) {
        if (curr == root) {
            root = nullptr;
        } else {
            if (curr->parent->left == curr) curr->parent->left = nullptr;
            else curr->parent->right = nullptr;
        }
        delete curr;
    }
    else if (curr->left != nullptr && curr->right != nullptr) {
        Node* succ = getMin(curr->right);
        Card succData = succ->info;
        
        remove(succData);
        curr->info = succData;
    }
    else {
        Node* child = (curr->left != nullptr) ? curr->left : curr->right;
        
        if (curr == root) {
            root = child;
            child->parent = nullptr;
        } else {
            if (curr->parent->left == curr) curr->parent->left = child;
            else curr->parent->right = child;
            child->parent = curr->parent;
        }
        delete curr;
    }
}


CardList::Iterator::Iterator(Node* n) {
    curr = n;
}

Card CardList::Iterator::operator*() const {
    return curr->info;
}

CardList::Iterator& CardList::Iterator::operator++() {
    if (curr == nullptr) return *this;

    if (curr->right != nullptr) {
        curr = curr->right;
        while (curr->left != nullptr) curr = curr->left;
    } else {
        Node* p = curr->parent;
        while (p != nullptr && curr == p->right) {
            curr = p;
            p = p->parent;
        }
        curr = p;
    }
    return *this;
}


CardList::Iterator& CardList::Iterator::operator--() {
    if (curr == nullptr) return *this;

    if (curr->left != nullptr) {
        curr = curr->left;
        while (curr->right != nullptr) curr = curr->right;
    } else {
        Node* p = curr->parent;
        while (p != nullptr && curr == p->left) {
            curr = p;
            p = p->parent;
        }
        curr = p;
    }
    return *this;
}

bool CardList::Iterator::operator==(const Iterator& other) const {
    return curr == other.curr;
}

bool CardList::Iterator::operator!=(const Iterator& other) const {
    return curr != other.curr;
}


CardList::Iterator CardList::begin() const {
    return Iterator(getMin(root));
}

CardList::Iterator CardList::end() const {
    return Iterator(nullptr);
}

CardList::Iterator CardList::rbegin() const {
    return Iterator(getMax(root));
}

CardList::Iterator CardList::rend() const {
    return Iterator(nullptr);
}
