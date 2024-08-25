#include <iostream>

using namespace std;


int hj22() {
    int input;
    while (cin >> input) {
        if (input == 0)break;

        std::cout << input / 2 << std::endl;
    }
    return 0;
}
