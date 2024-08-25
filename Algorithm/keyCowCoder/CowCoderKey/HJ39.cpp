#include <iostream>

int record[31] = {1};

int fib(int i) {
    if (i < 1) {
        return 0;
    }
    if (record[i - 1] != 0) {
        return record[i - 1];
    }
    int val = fib(i - 1) + fib(i - 2);
    record[i - 1] = val;

    return val;
}


int hj39() {
    int month;
    std::cin >> month;
    std::cout << fib(month);

    return 0;
}
