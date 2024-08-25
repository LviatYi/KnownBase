#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int hj68() {
    int count, order;
    while (cin >> count >> order) {
        std::vector<std::pair<string, int>> input(count);

        for (int i = 0; i < count; ++i) {
            std::string name;
            int score;

            std::cin >> name >> score;

            input[i] = {name, score};
        }

        std::stable_sort(
            input.begin(),
            input.end(),
            [&](
            const std::pair<std::string, int>& a,
            const std::pair<std::string, int>& b) {
                if (order == 1) return a.second < b.second;
                return a.second > b.second;
            });

        for (const auto e : input) {
            std::cout << e.first << " " << e.second << std::endl;
        }
    }

    return 0;
}
