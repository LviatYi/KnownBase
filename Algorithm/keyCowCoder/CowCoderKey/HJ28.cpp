#include <iostream>
#include <unordered_set>

void append_prime(std::vector<int>& prime_list, const int n) {
    if (prime_list.empty()) prime_list.push_back(2);

    for (int i = prime_list.back() + 1; i <= n; ++i) {
        bool isPrime = true;
        for (auto prime : prime_list) {
            if (i % prime == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) prime_list.push_back(i);
    }
}

bool is_prime(std::vector<int>& prime_list, const int n) {
    if (prime_list.empty() || prime_list.back() < n) append_prime(prime_list, n);
    if (prime_list.back() < n)return false;

    size_t l = 0;
    size_t r = prime_list.size();
    while (l < r) {
        size_t t = (l + r) / 2;
        if (prime_list[t] == n) return true;

        if (prime_list[t] < n) l = t + 1;
        else r = t;
    }

    return false;
}

struct Hj28Node {
    int val;
    size_t partner;
    std::vector<size_t> valid_partner;
};

bool node_partner_is_prime(const Hj28Node& lhs,
                           const Hj28Node& rhs,
                           std::vector<int>& prime_list) {
    return is_prime(prime_list, lhs.val + rhs.val);
}

int hj28() {
    int count;
    std::cin >> count;
    std::vector<int> even;
    std::vector<int> odd;
    while (count--) {
        int val;
        std::cin >> val;
        if (val % 2 == 0) {
            odd.push_back(val);
        } else {
            even.push_back(val);
        }
    }

    return 0;
}
