#include "Sword66.h"

std::vector<int> Sword66::constructArr(std::vector<int>& a) {
    if (a.empty()) {
        return a;
    }
    vector<int> lProd(a.size() - 1);
    vector<int> rProd(a.size() - 1);

    lProd.at(0) = 1;
    rProd.at(a.size() - 1) = 1;
    for (int i = 1; i < a.size(); ++i) {
        lProd.at(i) = lProd.at(i - 1) * a.at(i - 1);
    }
    for (int i = a.size() - 2; i >= 0; --i) {
        rProd.at(i) = rProd.at(i + 1) * a.at(i + 1);
    }

    vector<int> ans;
    for (int i = 0; i < a.size(); ++i) {
        ans.push_back(lProd.at(i) * rProd.at(i));
    }

    return ans;
}
