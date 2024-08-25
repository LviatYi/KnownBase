#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int hj32() {
    std::string input;

    while (std::cin >> input) {
        int max = 0;
        std::vector dp(input.size(),
                       std::vector<int>(input.size(),
                                        -1));

        for (int offset = 0; offset < 2; ++offset) {
            for (int i = 0; i < input.size(); ++i) {
                for (int j = 0; true; ++j) {
                    if (i - j < 0 ||
                        i + offset + j >= input.size()) {
                        break;
                    }
                    if (j == 0) {
                        if (offset == 0) {
                            dp[i][i] = 1;
                        } else if (input[i] == input[i + 1]) {
                            dp[i][i + offset] = 2;
                        } else {
                            break;
                        }
                    } else if (input[i - j] ==
                        input[i + offset + j]) {
                        dp[i - j][i + offset + j] =
                            dp[i - j + 1][i + offset + j - 1] + 2;
                    } else {
                        break;
                    }

                    if (dp[i - j][i + offset + j] > max) {
                        max = dp[i - j][i + offset + j];
                    }
                }
            }
        }

        std::cout << max << std::endl;
    }

    return 0;
}
