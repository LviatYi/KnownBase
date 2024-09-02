#include <iostream>
#include <vector>
using namespace std;

int odRun1() {
    int count;
    std::cin >> count;
    auto strength = std::vector<int>(count);
    auto lack = std::vector<int>(count - 1);

    for (int count_index = 0; count_index < count; ++count_index) {
        std::cin >> strength[count_index];
    }

    int last_strength = strength[0];
    for (int index = 1; index < strength.size(); ++index) {
        lack[index - 1] = std::max(100 - last_strength - strength[index], 0);
        last_strength = std::max(last_strength - 100, strength[index]);
    }

    last_strength = strength[strength.size() - 1];
    int lack_sum = 0;
    for (int index = strength.size() - 2; index >= 0; --index) {
        lack[index] = std::min(std::max(100 - last_strength - strength[index], 0), lack[index]);
        last_strength = std::max(last_strength - 100, strength[index]);
        lack_sum += lack[index];
    }


    // std::cout << lack_sum << std::endl;

    return lack_sum;
}

// 4
// 250 0 0 0
// 4
// 250 0 0 60
// 8
// 250 0 0 20 250 0 0 20
// 8
// 250 160 0 0 0 0 160 250
// 2
// 250 160
// 3
// 0 1000 0
// 3
// 0 50 0

int odRun1_2() {
    int count;
    std::cin >> count;
    auto result = std::vector<bool>((count - 1) * 100, false);

    int strength;
    for (int count_index = 0; count_index < count; ++count_index) {
        std::cin >> strength;
        int left = std::max(0, count_index * 100 - strength);
        int right = std::min(static_cast<int>(result.size()), count_index * 100 + strength);
        for (int i = left; i < right; ++i) {
            result[i] = true;
        }
    }

    int lack_sum = 0;
    for (auto r : result) {
        if (!r) {
            ++lack_sum;
        }
    }


    // std::cout << lack_sum << std::endl;

    return lack_sum;
}
