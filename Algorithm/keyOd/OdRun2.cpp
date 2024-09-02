#include <iostream>
#include <map>
#include <vector>
using namespace std;

int odRun2() {
    int row, col;
    std::cin >> row >> col;
    map<int, std::vector<std::pair<int, int>>> record;
    std::vector<std::vector<int>> data(row, std::vector<int>(col, 0));

    for (int row_index = 0; row_index < row; ++row_index) {
        for (int col_index = 0; col_index < col; ++col_index) {
            int value;
            std::cin >> value;
            data[row_index][col_index] = value;

            if (record.find(value) == record.end()) {
                record[value] = std::vector<std::pair<int, int>>();
            }

            record[value].emplace_back(row_index, col_index);
        }
    }

    for (int row_index = 0; row_index < row; ++row_index) {
        for (int col_index = 0; col_index < col; ++col_index) {
            int value = data[row_index][col_index];
            const auto& list = record[value];
            if (list.size() == 1) {
                data[row_index][col_index] = -1;
            } else {
                int min_distance = INT_MAX;
                for (auto location : list) {
                    int dist = abs(location.first - row_index) + abs(location.second - col_index);
                    if (dist == 0) {
                        continue;
                    }
                    if (dist < min_distance) {
                        min_distance = dist;
                    }
                }
                data[row_index][col_index] = min_distance;
            }
        }
    }

    std::cout << "[";

    for (int row_index = 0; row_index < row; ++row_index) {
        std::cout << "[";
        for (int col_index = 0; col_index < col; ++col_index) {
            std::cout << data[row_index][col_index];
            if (col_index < col - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        if (row_index < row - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]";

    return 0;
}
