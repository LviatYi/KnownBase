#include "Sword56.h"
#include<set>
#include<algorithm>
using std::set;
using std::max;

#pragma region Sword56_1
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
#pragma endregion
#pragma region Sword56_2

#pragma region 定义三进制异或运算
class ternary {
public:
    long long val;
    ternary(long _val) :val(_val) {}
    const ternary operator^(const ternary& rhs) {
        long long lval = this->val;
        long long rval = rhs.val;
        long long i = 1;
        long long greater = max(lval, rval);
        long long ans = 0;

        while (greater - 3 * i > 0) {
            i *= 3;
        }

        while (i > 0 && (lval != 0 || rval != 0)) {
            long long a = lval / i;
            long long b = rval / i;

            ans += (a + b) % 3 * i;

            lval -= a * i;
            rval -= b * i;

            i /= 3;
        }
        return ternary(ans);
    }

    ternary& operator^=(const ternary& rhs) {
        *this = (*this) ^ rhs;
        return *this;
    }
};

int Sword56::singleNumber(vector<int>& nums) {
    ternary ret(0);

    for (int num : nums) {
        ret ^= ternary(num);
    }

    return ret.val;
}
#pragma endregion

#pragma region 有限状态自动机
int Sword56::singleNumber2(vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int num : nums) {
        ones = ones ^ num & ~twos;
        twos = twos ^ num & ~ones;
    }
    return ones;
}
#pragma endregion

#pragma endregion