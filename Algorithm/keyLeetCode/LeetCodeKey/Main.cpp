#include "Main.h"

#include <algorithm>
#include <iostream>
#include <Solution22.h>
#include <Solution402.h>
#include <vector>

#include "Interval0808.h"
#include "LeetcodeUtil.h"
#include "Solution135.h"
#include "Solution1702.h"
#include "Solution179.h"
#include "Solution2617.h"
#include "Solution394.h"
#include "Solution45.h"
#include "Solution924.h"

using namespace std;

void test() {
}

int main() {
    auto solution = Interval0808();

    // const string input =
    //     "[2,3,1,1,4]";
    // const string input = "[[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]";
    // const string input = "[[2,1,0],[1,0,0]]";
    // const string input = "[[7,0,2,4],[0,2,3,0]]";
    // const auto input = "3[a2[c]]";

    auto input2 = std::vector<int>{3, 30, 34, 5, 9};

    // auto des = LeetcodeUtil::deserialize_vector_vector(input);
    // auto des = LeetcodeUtil::deserialize_vector_vector(input);
    // auto mapped_des = std::vector<std::vector<char>>(des.size(), std::vector<char>(des[0].size()));
    //
    // for (int i = 0; i < des.size(); ++i) {
    //     for (int j = 0; j < des[0].size(); ++j) {
    //         mapped_des[i][j] = des[i][j] == 1
    //                                ? '1'
    //                                : '0';
    //     }
    // }

    // for (auto& element : solution.generateParenthesis(input)) {
    //     std::cout << element << std::endl;
    // }

    solution.permutation("qqe");
}
