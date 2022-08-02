#include "Swordii4.h"
#include <unordered_map>

#pragma region 哈希表
int Swordii4::singleNumber(vector<int>& nums) {
	unordered_map<int, int> h;
	for (int num : nums) {
		auto itor = h.find(num);

		if (itor != h.end()) {
			if (itor->second == 2) {
				h.erase(itor);
			}
			else {
				itor->second++;
			}
		}
		else {
			h.insert({num, 1});
		}
	}

	return h.begin()->first;
}
#pragma endregion

#pragma region 按位确认
int Swordii4::singleNumber2(vector<int>& nums) {
	int ret = 0;
	for (int i = 0; i < 32; ++i) {
		int curr = 0;
		for (int num : nums) {
			curr += (num >> i) & 1;
		}
		ret += curr % 3 ? (1 << i) : 0;
	}
	return ret;
}
#pragma endregion
