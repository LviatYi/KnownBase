#include <iostream>
#include <vector>

int charToBit(char c) {
    if (c == 'l') {
        return 1;
    } else if (c == 'o') {
        return 2;
    } else if (c == 'x') {
        return 4;
    }
    return 0;
}

int od4206() {
    std::string input;
    std::cin >> input;
    input = input + input;

    int max = 0;
    auto dp = std::vector<std::vector<int>>(input.size(), std::vector<int>(input.size(), 0));
    for (int start_index = 0; start_index < input.size(); ++start_index) {
        dp[start_index][start_index] |= charToBit(input[start_index]);
    }

    for (int start_at = 0; start_at < input.size() / 2; ++start_at) {
        for (int end_at = start_at + 1; end_at < start_at + input.size() / 2; ++end_at) {
            dp[start_at][end_at] = dp[start_at][end_at - 1] ^ charToBit(input[end_at]);

            if (dp[start_at][end_at] == 0 && end_at - start_at + 1 > max) {
                max = end_at - start_at + 1;
            }
        }
    }

    std::cout << max << std::endl;

    return 0;
}
