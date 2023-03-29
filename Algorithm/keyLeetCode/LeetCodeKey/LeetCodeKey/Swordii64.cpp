#include "Swordii64.h"

bool Swordii64::sub_search(std::string& searchWord, size_t index, Swordii64::character_dict* current, int tolerance) {
    if (tolerance < 0) {
        return false;
    }

    if (index >= searchWord.size()) {
        return tolerance == 0 && current->is_end;
    }

    for (int i = 0; i < character_dict::size - 1; ++i) {
        if (current->chars[i] == nullptr) {
            continue;
        }

        if (i == searchWord[index] - 'a' && current->chars[i] != nullptr && sub_search(
                searchWord, index + 1, current->chars[i], tolerance)
            || i != searchWord[index] - 'a' && current->chars[i] != nullptr && sub_search(
                searchWord, index + 1, current->chars[i], tolerance - 1)) {
            return true;
        }
    }

    return false;
}

Swordii64::Swordii64() {
    dict = new character_dict();
}

void Swordii64::buildDict(std::vector<std::string> dictionary) {
    for (auto string : dictionary) {
        character_dict* current = dict;

        for (const char c : string) {
            if (current->chars[c - 'a'] == nullptr) {
                current->chars[c - 'a'] = new character_dict;
            }
            current = current->chars[c - 'a'];
        }

        current->is_end = true;
    }
}

bool Swordii64::search(std::string searchWord) {
    return sub_search(searchWord, 0, dict, 1);
}
