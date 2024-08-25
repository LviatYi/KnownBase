#include "Swordii36.h"

#include <stack>

int Swordii36::evalRPN(std::vector<std::string>& tokens) {
    std::stack<int> stack = {};

    for (auto token : tokens) {
        if (token.size() > 1 || std::isdigit(token[0])) {
            int num = 0;
            int neg_flag = 1;
            if (token[0] == '-' || token[0] == '+') {
                token = token.substr(1, token.size() - 1);
                neg_flag = -1;
            }

            for (const char j : token) {
                num *= 10;
                num += j - '0';
            }

            stack.push(num * neg_flag);
        }
        else {
            int ret = 0;
            const int rhs = stack.top();
            stack.pop();
            const int lhs = stack.top();
            stack.pop();

            if (token == "+") {
                ret = lhs + rhs;
            }
            else if (token == "-") {
                ret = lhs - rhs;
            }
            else if (token == "*") {
                ret = lhs * rhs;
            }
            else if (token == "/") {
                ret = lhs / rhs;
            }
            stack.push(ret);
        }
    }

    return stack.top();
}
