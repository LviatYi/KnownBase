#include "Solution30.h"
#include <unordered_map>
#include <queue>

using namespace std;

int getOrder(unordered_map<string, int>& keyMap, string subStr) {
    int order = -1;
    unordered_map<string, int>::iterator i = keyMap.find(subStr);
    if (i != keyMap.end()) {
        order = i->second;
    }

    return order;
}

vector<int> Solution30::findSubstring(string s, vector<string>& words) {
    vector<int> ans;

    // 可选数量，出现位置
    pair<int, queue<int>*>* keyTable = (pair<int, queue<int>*>*)malloc(sizeof(pair<int, queue<int>*>) * words.size());
    if (!keyTable) {
        return ans;
    }
    for (int i = 0; i < words.size(); i++) {
        queue<int> empty;
        keyTable[i].first = 1;
        keyTable[i].second = new queue<int>();
    }

    // 关键词串，索引
    unordered_map<string, int> keyMap;
    for (int i = 0; i < words.size(); i++) {
        unordered_map<string, int>::iterator p = keyMap.find(words[i]);
        if (p == keyMap.end()) {
            keyMap.insert(pair<string, int>(words[i], i));
        }
        else {
            keyTable[p->second].first++;
        }
    }

    // 检索起始位置，检出量
    int start = 0, count = 0;
    int wordLen = words[0].length();

    for (int start = 0, count = 0; start + wordLen * words.size() <= s.length(); start++) {
        // 检索到第一个词
        int order = getOrder(keyMap, s.substr(start, wordLen));
        if (order != -1) {
            bool reset = false;
            keyTable[order].second->push(start);
            count++;
            while (true) {
                if (count * wordLen >= words.size() * wordLen) {
                    // 成功找到
                    ans.push_back(start);
                    reset = true;
                    break;
                }

                int newWordOrder = getOrder(keyMap, s.substr(start + count * wordLen, wordLen));

                if (newWordOrder != -1 && keyTable[newWordOrder].second->size() != keyTable[newWordOrder].first) {
                    count++;
                    keyTable[newWordOrder].second->push(start + count * wordLen - wordLen);
                }
                else {
                    reset = true;
                    break;
                }
            }

            if (reset) {
                reset = false;
                count = 0;
                for (int i = 0; i < keyMap.size(); i++) {
                    queue<int> empty;
                    keyTable[i].second->swap(empty);
                }
            }
        }
    }

    return ans;
}

