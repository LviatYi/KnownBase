#include "Swordii1.h"
#include <limits>

/// <summary>
/// 快速除法
/// 为避免 int 型溢出，参数都为负数。
/// </summary>
/// <param name="dividend"></param>
/// <param name="divisor"></param>
/// <returns></returns>
static int quickDiv(int dividend, int divisor) {
	if (dividend > divisor) {
		return 0;
	}

	int ans = 1;
	int sumDivisor = divisor;

	while (sumDivisor > dividend - sumDivisor) {
		// 翻倍
		sumDivisor += sumDivisor;
		ans += ans;
	}

	return ans + quickDiv(dividend - sumDivisor, divisor);
}


int Swordii1::divide(int dividend, int divisor) {
	if (dividend == 0) return 0;
	if (divisor == 1) return dividend;
	if (divisor == -1) {
		if (dividend > INT_MIN) return -dividend;
		return INT_MAX;
	}

	bool isNeg = (divisor < 0 && dividend < 0 || divisor > 0 && dividend > 0) ? false : true;

	dividend = dividend < 0 ? dividend : -dividend;
	divisor = divisor < 0 ? divisor : -divisor;

	return isNeg ? -quickDiv(dividend, divisor) : quickDiv(dividend, divisor);
}
