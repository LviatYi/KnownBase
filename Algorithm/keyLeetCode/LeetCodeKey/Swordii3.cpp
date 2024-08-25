#include "Swordii3.h"
#include <bitset>
#pragma region 位运算函数
vector<int> Swordii3::countBits(int n) {
	vector<int> rets(n + 1);
	for (int i = 0; i < n + 1; ++i) {
		rets.at(i) = static_cast<int>(bitset<sizeof(int) * 8>(i).count());
	}

	return rets;
}
#pragma endregion


#pragma region 二分法
vector<int> Swordii3::countBits2(int n) {
	vector<int> rets(n + 1);

	for (int i = 0; i < n + 1; ++i) {
		int ret = i;
		ret = (ret & 0x55555555) + ((ret >> 1) & 0x55555555);
		ret = (ret & 0x33333333) + ((ret >> 2) & 0x33333333);
		ret = (ret & 0x0f0f0f0f) + ((ret >> 4) & 0x0f0f0f0f);
		ret = (ret & 0x00ff00ff) + ((ret >> 8) & 0x00ff00ff);
		ret = (ret & 0x0000ffff) + ((ret >> 16) & 0x0000ffff);

		rets.at(i) = ret;
	}

	return rets;
}
#pragma endregion

#pragma region 末位清零
// 对任意正整数 -1 ，其二进制表示中最后一位出现的 1 必然将变为 0 .
vector<int> Swordii3::countBits3(int n) {
	vector<int> rets(n + 1);

	for (int i = 0; i < n + 1; ++i) {
		int cnt = i;
		int ret = 0;
		while (cnt > 0) {
			cnt = (cnt - 1) & cnt;
			ret++;
		}
		rets.at(i) = ret;
	}

	return rets;
}
#pragma endregion
