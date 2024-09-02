#include <iostream>
using namespace std;

int odRun1() {
    int count;
    int strength;
    int last_strength = 100000 * 100;
    int lack = 0;
    std::cin >> count;

    for (int count_index = 0; count_index < count; ++count_index) {
        std::cin >> strength;
        lack += last_strength + strength > 100 ? 0 : 100 - last_strength - strength;
        last_strength = last_strength > strength + 100 ? last_strength - 100 : strength;
    }

    std::cout << lack << std::endl;

    return 0;
}
