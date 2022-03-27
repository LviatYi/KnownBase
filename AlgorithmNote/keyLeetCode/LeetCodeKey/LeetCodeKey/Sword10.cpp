#include "Sword10.h"
using namespace std;

int Sword10::fib(int n) {
    static unordered_map<int, int> dp{ {0, 0}, {1, 1} };

    if (dp.find(n) == dp.end()) {
        long long sum = (long long)fib(n - 1) + (long long)fib(n - 2);
        dp.insert({ n, sum % 1000000007 });
    }

    return dp.find(n)->second ;
}
