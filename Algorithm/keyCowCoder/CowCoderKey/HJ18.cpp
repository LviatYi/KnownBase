#include <iostream>
#include <regex>
#include <string>

struct Address {
    int fst;
    int snd;
    int thd;
    int fth;

    static constexpr int invalid_val = -1;

    const static std::regex pattern;

    static Address A_MIN;
    static Address A_MAX;
    static Address B_MIN;
    static Address B_MAX;
    static Address C_MIN;
    static Address C_MAX;
    static Address D_MIN;
    static Address D_MAX;
    static Address E_MIN;
    static Address E_MAX;
    static Address PRIVATE_MIN_0;
    static Address PRIVATE_MAX_0;
    static Address PRIVATE_MIN_1;
    static Address PRIVATE_MAX_1;
    static Address PRIVATE_MIN_2;
    static Address PRIVATE_MAX_2;

    static std::smatch matches;

public:
    Address(int fst, int snd, int thd, int fth) {
        this->fst = fst;
        this->snd = snd;
        this->thd = thd;
        this->fth = fth;
    }

    Address(std::string& str) {
        if (str.compare(0, 2, "0.") == 0) {
            fst = 0;
        } else if (str.compare(0, 4, "127.") == 0) {
            fst = 127;
        } else if (std::regex_match(str.cbegin(),
                                    str.cend(),
                                    matches,
                                    pattern)) {
            this->fst = std::stoi(matches[1].str());
            this->snd = std::stoi(matches[2].str());
            this->thd = std::stoi(matches[3].str());
            this->fth = std::stoi(matches[4].str());
        } else {
            this->fst = invalid_val;
            this->snd = invalid_val;
            this->thd = invalid_val;
            this->fth = invalid_val;
        }
    }

    bool is_valid() {
        return this->fst >= 0 && this->fst < 256 &&
            this->snd >= 0 && this->snd < 256 &&
            this->thd >= 0 && this->thd < 256 &&
            this->fth >= 0 && this->fth < 256;
    }

    bool is_start_with_0() {
        return this->fst == 0;
    }

    bool is_start_with_127() {
        return this->fst == 127;
    }

    char judge_type() {
        if (*this > Address::A_MIN && *this < Address::A_MAX) {
            return 'A';
        } else if (*this >= Address::B_MIN && *this <= Address::B_MAX) {
            return 'B';
        } else if (*this >= Address::C_MIN && *this <= Address::C_MAX) {
            return 'C';
        } else if (*this >= Address::D_MIN && *this <= Address::D_MAX) {
            return 'D';
        } else if (*this >= Address::E_MIN && *this <= Address::E_MAX) {
            return 'E';
        } else return ' ';
    }

    bool is_valid_as_mask() {
        const int val = (this->fst << 24)
            + (this->snd << 16)
            + (this->thd << 8)
            + (this->fth);
        int p = 31;
        while (p >= 0 && val & (1 << p)) {
            --p;
        }
        if (p == 31 || p < 0) return false;

        while (p >= 0 && !(val & (1 << p))) {
            --p;
        }

        return p == -1;
    }

    bool is_private() {
        return
            (*this >= Address::PRIVATE_MIN_0 && *this <= Address::PRIVATE_MAX_0) ||
            (*this >= Address::PRIVATE_MIN_1 && *this <= Address::PRIVATE_MAX_1) ||
            (*this >= Address::PRIVATE_MIN_2 && *this <= Address::PRIVATE_MAX_2);
    }

    bool operator<(const Address& rhs) {
        return std::tie(fst, snd, thd, fth) < std::tie(rhs.fst, rhs.snd, rhs.thd,
                                                       rhs.fth);
    }

    bool operator>(const Address& rhs) {
        return std::tie(fst, snd, thd, fth) > std::tie(rhs.fst, rhs.snd, rhs.thd,
                                                       rhs.fth);
    }

    bool operator<=(const Address& rhs) {
        return !(*this > rhs);
    }

    bool operator>=(const Address& rhs) {
        return !(*this < rhs);
    }
};

const std::regex Address::pattern
    = std::regex(
        R"(^([0-9]+).([0-9]+).([0-9]+).([0-9]+))");

std::smatch Address::matches
    = std::smatch();

Address Address::A_MIN = Address(1, 0, 0, 0);
Address Address::A_MAX = Address(126, 255, 255, 255);
Address Address::B_MIN = Address(128, 0, 0, 0);
Address Address::B_MAX = Address(191, 255, 255, 255);
Address Address::C_MIN = Address(192, 0, 0, 0);
Address Address::C_MAX = Address(223, 255, 255, 255);
Address Address::D_MIN = Address(224, 0, 0, 0);
Address Address::D_MAX = Address(239, 255, 255, 255);
Address Address::E_MIN = Address(240, 0, 0, 0);
Address Address::E_MAX = Address(255, 255, 255, 255);
Address Address::PRIVATE_MIN_0 = Address(10, 0, 0, 0);
Address Address::PRIVATE_MAX_0 = Address(10, 255, 255, 255);
Address Address::PRIVATE_MIN_1 = Address(172, 16, 0, 0);
Address Address::PRIVATE_MAX_1 = Address(172, 31, 255, 255);
Address Address::PRIVATE_MIN_2 = Address(192, 168, 0, 0);
Address Address::PRIVATE_MAX_2 = Address(192, 168, 255, 255);

int hj18() {
    std::string input;
    int a_count = 0;
    int b_count = 0;
    int c_count = 0;
    int d_count = 0;
    int e_count = 0;
    int invalid_count = 0;
    int private_count = 0;
    while (std::cin >> input) {
        auto s = input.find('~');

        if (s != std::string::npos) {
            std::string addr_s = input.substr(0, s);
            std::string addr_m = input.substr(s + 1, input.size());
            auto addr = Address(addr_s);
            auto mask = Address(addr_m);

            if (addr.is_start_with_0() || addr.is_start_with_127()) {
                continue;
            } else if (!addr.is_valid() || !mask.is_valid_as_mask()) {
                ++invalid_count;
            } else {
                switch (addr.judge_type()) {
                case 'A':
                    ++a_count;
                    break;
                case 'B':
                    ++b_count;
                    break;
                case 'C':
                    ++c_count;
                    break;
                case 'D':
                    ++d_count;
                    break;
                case 'E':
                    ++e_count;
                    break;
                default:
                    break;
                }

                if (addr.is_private()) {
                    ++private_count;
                }
            }
        }
    }

    std::cout <<
        a_count <<
        " " <<
        b_count <<
        " " <<
        c_count <<
        " " <<
        d_count <<
        " " <<
        e_count <<
        " " <<
        invalid_count <<
        " " <<
        private_count <<
        std::endl;

    return 0;
}
