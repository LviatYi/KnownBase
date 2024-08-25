#include "Solution20.h"
#include <stack>
#include <unordered_map>

using namespace std;

bool Solution20::isValid(std::string s) {
    std::stack<char> container;
    bool isValid = true;

    unordered_map<char, char> symbols = {
            {')', '('},
            {']', '['},
            {'}', '{'}
    };

    for (char c : s) {
        auto i = symbols.find(c);
        if (i != symbols.end()) {
            if (!container.empty() && (*i).second == container.top()) {
                container.pop();
            }
            else {
                isValid = false;
            }

        }
        else {
            container.push(c);
        }

    }

    return isValid && container.empty();
}
