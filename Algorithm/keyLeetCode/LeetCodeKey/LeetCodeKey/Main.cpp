#include "Main.h"
#include "Solutions.h"
#include "ListNode.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
	Swordii3 s;

	vector<int> ret;
	ret = s.countBits(10);
	for (int ret1 : ret) {
		std::cout << ret1 << endl;
	}

	std::cout << "--------------------------------" << endl;
	ret = s.countBits2(10);
	for (int ret1 : ret) {
		std::cout << ret1 << endl;
	}

	std::cout << "--------------------------------" << endl;
	ret = s.countBits3(10);
	for (int ret1 : ret) {
		std::cout << ret1 << endl;
	}

}
