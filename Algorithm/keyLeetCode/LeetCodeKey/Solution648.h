#pragma once
#include <string>
#include <vector>

class Solution648 {
private:
    class Trie {
    private:
        struct TrieNode {
            std::vector<TrieNode*> char_table = std::vector<TrieNode*>(26);
            bool is_end_ = false;

            bool has_char(const char& c) const;
        };

        TrieNode* tree;
    public:
        /** Initialize your data structure here. */
        Trie();

        /** Inserts a word into the trie. */
        void insert(std::string word);

        /** Returns if the word is in the trie. */
        std::string search_prefix(std::string word);
    };

    Trie trie_;
public:
    std::string replaceWords(std::vector<std::string>& dictionary, std::string sentence);
};
