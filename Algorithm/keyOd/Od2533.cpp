#include <iostream>
#include <string>
#include <vector>

int od2533() {
    std::string input;
    std::cin >> input;

    std::vector<int> map;
    std::vector<int> mountains;

    size_t last = 0;
    while (last < input.size()) {
        size_t p = input.find(',', last);
        if (p == std::string::npos) {
            p = input.size();
        }
        int val = std::stoi(input.substr(last, p));
        map.push_back(val);
        last = p + 1;
    }

    int cost=0;
    // int

    for (int i = 0; i < map.size(); ++i) {
        
    }

    return 0;
}
