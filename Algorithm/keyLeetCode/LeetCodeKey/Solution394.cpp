#include "Solution394.h"

#include <locale>
#include <stack>
#include <string>

std::string Solution394::decodeString(std::string s) {
    std::stack<std::string::iterator> stk;
    std::stack<int> count_stk;
    std::stack<std::string> frag_stack;
    frag_stack.emplace("");
    int count = 0;

    for (auto p = s.begin(); p < s.end(); ++p) {
        if (*p == '[') {
            stk.push(p);
            count_stk.push(count);
            frag_stack.push("");
            count = 0;
        } else if (*p == ']') {
            auto begin = stk.top();
            std::string repeat = "";
            auto count = count_stk.top();
            while (count--) {
                repeat += frag_stack.top();
            }
            stk.pop();
            count_stk.pop();
            frag_stack.pop();
            frag_stack.top() += repeat;
        } else if (std::isdigit(*p)) {
            count *= 10;
            count += *p - '0';
        } else {
            frag_stack.top() += *p;
        }
    }

    return frag_stack.top();
}
