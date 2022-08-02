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
	Swordii4 s;
	vector<int> v{1, 2, 2, 1, 3, 2, 1};
	int ret = s.singleNumber(v);
	std::cout << ret << endl;
}
