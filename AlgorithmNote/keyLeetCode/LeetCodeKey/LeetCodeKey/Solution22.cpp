#include "Solution22.h"
#include<memory>

using namespace std;

// 计算结果缓存
shared_ptr<vector<string>> cache[9] = { nullptr };

shared_ptr<vector<string>> generate(int n) {
    if (cache[n] != nullptr) {
        return cache[n];
    }
    shared_ptr<vector<string>> ans = shared_ptr<vector<string>>(new vector<string>);
    if (n == 0) {
        ans->push_back("");
    }
    else {
        for (int i = 0; i <= n - 1; i++) {
            for (string str1 : *generate(i)) {
                for (string str2 : *generate(n - 1 - i)) {
                    // f(x) 可能出现的括号串为 "(f(i))+f(x-1-i)"
                    ans->push_back("(" + str1 + ")" + str2);
                }
            }
        }
    }
    cache[n] = ans;
    return ans;
}

std::vector<std::string> Solution22::generateParenthesis(int n) {
    return *generate(n);
}