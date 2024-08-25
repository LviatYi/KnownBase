#include "Solution402.h"

using namespace std;

std::string Solution402::removeKdigits(std::string num, int k) {
    std::string output = "";
    int i = 0;
    for (; i < num.size(); ++i) {
        if (i == 0) {
            output.push_back(num[i]);
            continue;
        }

        while (!output.empty() && *(output.end() - 1) > num[i] && k > 0) {
            output.pop_back();
            --k;
        }

        output.push_back(num[i]);
    }


    if (k > 0) {
        output = output.substr(0,
                               std::max<int>(
                                   output.size() - k,
                                   0));
    }

    int pos_0 = output.find_first_not_of('0');
    if (pos_0 == string::npos || output.empty()) {
        return "0";
    }

    return output.substr(pos_0);
}
