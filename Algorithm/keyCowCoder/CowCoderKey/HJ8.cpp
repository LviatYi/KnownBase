#include "Solutions.h"

#include <iostream>
#include <map>

int hj8() {
    int count;
    while (std::cin >> count) {
        auto record = std::map<int, int>();

        for (int i = 0; i < count; ++i) {
            int index;
            int val;
            std::cin >> index >> val;

            if (record.find(index) == record.end()) {
                record.insert({index, val});
            } else {
                record.insert_or_assign(index, record.at(index) + val);
            }
        }

        for (const auto pair : record) {
            std::cout << pair.first << " " << pair.second << '\n';
        }
    }

    return 0;
}
