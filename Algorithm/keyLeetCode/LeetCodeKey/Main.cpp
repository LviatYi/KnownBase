#include "Main.h"

#include <iostream>
#include <Solution1094.h>
#include <vector>

#include "LeetcodeUtil.h"
#include "Solution253.h"

using namespace std;

void test() {
}

int main() {
    auto solution = Solution253();

    // const string input =
    //     "[2,3,1,1,4]";
    // const string input = "[[5,8],[6,8]]";
    // const string input = "[[0,1],[0,2],[0,3],[1,2],[1,3],[1,4]]";
    // const string input = "[[0,30],[5,10],[15,20]]";
    const string input = "[[13,15],[1,13]]";
    // const string input = "[[2,1,0],[1,0,0]]";
    // const string input = "[[7,0,2,4],[0,2,3,0]]";
    // const auto input = "3[a2[c]]";

    auto input2 = std::vector<int>{1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};

    auto des = LeetcodeUtil::deserialize_vector_vector(input);
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

    std::cout << solution.minMeetingRooms(des);
    // solution.lengthOfLIS(input2);
}
