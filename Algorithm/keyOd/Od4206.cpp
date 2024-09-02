#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int od4500() {
    int count;
    int input_relation_size;
    std::cin >> count >> input_relation_size;
    auto relation_map = std::vector<std::array<int, 3>>(input_relation_size);

    for (int input_index = 0; input_index < input_relation_size; ++input_index) {
        int f, t, c, connected;
        std::cin >> f >> t >> c >> connected;
        if (connected == 1) {
            c = 0;
        }
        relation_map[input_index][0] = f - 1;
        relation_map[input_index][1] = t - 1;
        relation_map[input_index][2] = c;
    }

    std::sort(relation_map.begin(), relation_map.end(), [](const auto& lhs, const auto& rhs) {
        return lhs[2] < rhs[2];
    });

    auto connected = std::vector<bool>(count, false);
    connected[0] = true;

    int connected_count = 1;
    int cost = 0;
    bool progress = true;
    while (connected_count < count && progress) {
        progress = false;
        for (int rela_index = 0; rela_index < relation_map.size(); ++rela_index) {
            const auto rela = relation_map[rela_index];
            if (connected[rela[0]] && connected[rela[1]]) {
                continue;
            }

            if (connected[rela[0]] || connected[rela[1]]) {
                connected[rela[0]] = true;
                connected[rela[1]] = true;
                ++connected_count;
                cost += rela[2];
                progress = true;
                break;
            }
        }
    }

    if (connected_count == count) {
        std::cout << cost << std::endl;
    } else {
        std::cout << "-1" << std::endl;
    }

    return 0;
}
