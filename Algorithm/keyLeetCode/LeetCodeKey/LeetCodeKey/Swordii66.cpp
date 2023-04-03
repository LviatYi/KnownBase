#include "Swordii66.h"

#include <stack>

void Swordii66::Character_dict::insert(std::string& word, const int& end_val, int index) {
    if (index == word.size()) {
        this->val = end_val;
        return;
    }
    if (index > word.size()) {
        return;
    }

    if (chars[word[index] - 'a'] == nullptr) {
        chars[word[index] - 'a'] = new Character_dict;
    }

    chars[word[index] - 'a']->insert(word, end_val, index + 1);
}

Swordii66::Swordii66() {
    dict_ = new Character_dict;
}

void Swordii66::insert(std::string key, int val) {
    dict_->insert(key, val);
}

int Swordii66::sum(std::string prefix) {
    Character_dict* current = dict_;
    int ret = 0;

    for (char c : prefix) {
        if (current->chars[c - 'a'] != nullptr) {
            current = current->chars[c - 'a'];
        }
        else {
            return 0;
        }
    }

    std::stack<Character_dict*> stack;
    stack.push(current);

    while (!stack.empty()) {
        current = stack.top();
        stack.pop();
        ret += current->val;

        for (auto& char_dict : current->chars) {
            if (char_dict != nullptr) {
                stack.push(char_dict);
            }
        }
    }

    return ret;
}
