#include "Swordii62.h"

bool Swordii62::TrieNode::has_char(const char& c) const {
    return char_table[c - 'a'] != nullptr;
}

Swordii62::Swordii62() {
    tree = new TrieNode;
}

void Swordii62::insert(std::string word) {
    TrieNode* current = tree;

    for (const char& i : word) {
        TrieNode* next = current->char_table[i - 'a'];

        if (next == nullptr) {
            next = new TrieNode();
            current->char_table[i - 'a'] = next;
        }

        current = next;
    }

    current->is_end_ = true;
}

bool Swordii62::search(std::string word) {
    TrieNode* current = tree;

    for (const char& i : word) {
        if (current == nullptr || !current->has_char(i)) {
            return false;
        }

        current = current->char_table[i - 'a'];
    }

    return current != nullptr && current->is_end_;
}

bool Swordii62::startsWith(std::string prefix) {
    TrieNode* current = tree;

    for (const char& i : prefix) {
        if (current == nullptr || !current->has_char(i)) {
            return false;
        }

        current = current->char_table[i - 'a'];
    }

    return true;
}
