#include "Sword40.h"
#include<algorithm>
using std::sort;

vector<int> Sword40::getLeastNumbers(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());

    return vector<int>(arr.begin(), arr.begin() + k);
}
