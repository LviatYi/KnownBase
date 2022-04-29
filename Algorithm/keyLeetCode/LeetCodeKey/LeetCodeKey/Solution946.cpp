#include "Solution946.h"

#include <stack>

using std::stack;

#pragma region 双指针
bool Solution946::validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    int pushPos = 0;
    int popPos = 0;

    while (pushPos < pushed.size() && popPos < popped.size()) {
        if (pushed[pushPos] != popped[popPos]) {
            pushPos++;
            while (pushPos < pushed.size() && pushed[pushPos] == -1) {
                pushPos++;
            }
        }
        else {
            pushed[pushPos] = -1;
            while (pushPos > 0 && pushed[--pushPos] == -1) {
            }
            popPos++;
        }
    }

    return popPos == popped.size();
}
#pragma endregion

#pragma region 模拟
bool Solution946::validateStackSequences2(vector<int>& pushed, vector<int>& popped) {
    stack<int> s;
    int pushPos = 0;

    for (int i : popped) {
        while ((s.empty() || i != s.top()) && pushPos < pushed.size()) {
            s.push(pushed[pushPos++]);
        }
        if (i == s.top()) {
            s.pop();
            continue;
        }
        else {
            break;
        }
    }
    return s.empty();
}
#pragma endregion
