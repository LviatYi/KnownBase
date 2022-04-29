#include "Sword17.h"

vector<int> Sword17::printNumbers(int n) {
    int count = 1;
    vector<int> ans;

    for (int i = 0; i < n; i++) {
        count *= 10;
    }

    for (int i = 1; i < count; i++) {
        ans.push_back(i);
    }
    return ans;
}
