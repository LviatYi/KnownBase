#include "Sword62.h"

#pragma region 递归法
/// <summary>
/// 求得剩下的唯一数字在数组中的位置。
/// </summary>
/// <param name="n">数组长度</param>
/// <param name="m">删除周期</param>
/// <returns></returns>
static int f(int n, int m) {
    if (n == 1) {
        return 0;
    }

    // 递归
    // x 为剩下的数字在子数组中的位置。
    int x = f(n - 1, m);
    // 计算 子数组中的 x 在原数组的位置。
    return (m + x) % n;
}

int Sword62::lastRemaining(int n, int m) {
    return f(n, m);
}
#pragma endregion
#pragma region 循环解除递归
int Sword62::lastRemaining2(int n, int m) {
    int pos = 0;
    for (int i = 0; i < n; i++) {
        pos = (m + pos) % (i + 1);
    }
    return pos;
}
#pragma endregion