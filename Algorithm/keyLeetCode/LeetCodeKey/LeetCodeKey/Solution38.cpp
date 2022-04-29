#include "Solution38.h"
#include <vector>

using namespace std;

static vector<string> anss(30, "");

string Solution38::countAndSay(int n) {
    if (n == 1) {
        return "1";
    }

    if (anss[n - 1] != "") {
        return anss[n - 1];
    }

    string str = countAndSay(n - 1);
    string ans;

    int last = 0;
    int  count = 0;

    for (char c : str) {
        if (last == 0) {
            last = c - '0';
            count++;
        }
        else if (last == 0 || c - '0' == last) {
            count++;
        }
        else {
            ans += to_string(count) + to_string(last);

            last = c - '0';
            count = 1;
        }
    }
    ans += to_string(count) + to_string(last);

    anss[n - 1] = ans;
    return ans;
}
