#include "Solution648.h"

bool Solution648::Trie::TrieNode::has_char(const char& c) const {
    return char_table[c - 'a'] != nullptr;
}

Solution648::Trie::Trie() {
    tree = new TrieNode;
}

void Solution648::Trie::insert(std::string word) {
    TrieNode* current = tree;

    for (const char& i : word) {
        TrieNode* next = current->char_table[i - 'a'];

        if (next == nullptr) {
            next = new TrieNode();
            current->char_table[i - 'a'] = next;
        }
        else {
            if (next->is_end_) {
                return;
            }
        }

        current = next;
    }

    current->is_end_ = true;
    for (auto& i : current->char_table) {
        delete i;
        i = nullptr;
    }
}

std::string Solution648::Trie::search_prefix(std::string word) {
    std::string prefix;
    std::string last_prefix;
    TrieNode* current = tree;

    for (const char& i : word) {
        if (current == nullptr || !current->has_char(i)) {
            break;
        }
        if (current->is_end_) {
            last_prefix = prefix;
        }
        prefix.push_back(i);
        current = current->char_table[i - 'a'];
    }
    if (current->is_end_) {
        last_prefix = prefix;
    }

    return last_prefix;
}

std::string Solution648::replaceWords(std::vector<std::string>& dictionary, std::string sentence) {
    for (auto string : dictionary) {
        trie_.insert(string);
    }

    std::string ret;
    int start = 0;
    int length = 0;

    for (int i = 0; i <= sentence.size(); ++i, ++length) {
        if (i == sentence.size() || sentence[i] == ' ') {
            std::string word = sentence.substr(start, length);
            std::string prefix = trie_.search_prefix(word);
            if (!prefix.empty()) {
                word = prefix;
            }

            ret += i == sentence.size() ? word : word + ' ';

            start = start + length + 1;
            length = -1;
        }
    }

    return ret;
}
