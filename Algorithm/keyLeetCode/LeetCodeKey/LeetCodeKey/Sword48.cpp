#include "Sword48.h"
#include <unordered_map>

using namespace std;

int Sword48::lengthOfLongestSubstring(string s) {
    // 哈希优化
    unordered_map<char, int> hashTable;
    int maxLength = 0;
    int cutBegin = -1;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        auto itor = hashTable.find(c);
        if (itor == hashTable.end()) {
            // 没有相同符号
            hashTable.insert(make_pair(c, i));
        }
        else {
            // 有相同符号
            if ((*itor).second >= cutBegin) {
                // 有效段中有相同符号
                maxLength = maxLength > i - cutBegin - 1 ? maxLength : i - cutBegin - 1;
                cutBegin = (*itor).second;
            }
            (*itor).second = i;
        }
    }
    return s.length() - cutBegin - 1 > maxLength ? s.length() - 1 - cutBegin : maxLength;
}

int Sword48::lengthOfLongestSubstring2(string s) {
    // 桶优化
    int* characterTable = new int[128];
    int thisLength = 0;
    int maxLength = 0;
    int start = -1;

    memset(characterTable, -1, sizeof(int) * 128);

    for (int i = 0; i < s.length(); i++) {
        if (characterTable[s[i]] > start) {
            // 有相同符号
            thisLength = i - characterTable[s[i]];
            start = characterTable[s[i]];
        }
        else {
            // 没有相同符号
            thisLength++;
        }

        characterTable[s[i]] = i;
        if (thisLength > maxLength) {
            maxLength = thisLength;
        }
    }

    delete[] characterTable;
    return maxLength;
}