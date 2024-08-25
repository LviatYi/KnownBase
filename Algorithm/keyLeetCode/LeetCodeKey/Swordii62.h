#pragma once
#include <string>
#include <vector>

class Swordii62 {
private:
    struct TrieNode {
        std::vector<TrieNode*> char_table = std::vector<TrieNode*>(26);
        bool is_end_;

        bool has_char(const char& c) const;
    };

    TrieNode* tree;
public:
    /** Initialize your data structure here. */
    Swordii62();

    /** Inserts a word into the trie. */
    void insert(std::string word);

    /** Returns if the word is in the trie. */
    bool search(std::string word);

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix);
};
