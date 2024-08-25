#include <iostream>

int hj36() {
    int n;
    while (std::cin >> n) {
        int k = 1;
        for (int i = 1; i <= n; i++) {
            std::cout << k << " ";
            int temp = k;
            for (int j = i + 1; j <= n; j++) {
                temp += j;
                std::cout << temp << " ";
            }
            std::cout << std::endl;
            k += i;
        }
    }

    return 0;
}
