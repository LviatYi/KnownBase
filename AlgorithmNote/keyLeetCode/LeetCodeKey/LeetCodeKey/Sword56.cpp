#include "Sword56.h"
#include<set>
using std::set;

vector<int> Sword56::singleNumbers(vector<int>& nums) {
    // 设两不同数为 x,y
    int ret = 0;
    for (int num : nums) {
        ret ^= num;
    }
    // 获得 x ^ y

    // 寻找 x ^ y 首个不同 bit
    int div = 1;
    while (!(ret & div)) {
        div <<= 1;
    }

    int a = 0;
    int b = 0;

    // 将数组分为两组
    for (int num : nums) {
        if (num & div) {
            a ^= num;
        }
        else {
            b ^= num;
        }
    }

    return { a,b };
}
