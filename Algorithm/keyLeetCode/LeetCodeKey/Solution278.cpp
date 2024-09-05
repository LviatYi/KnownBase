#include "Solution278.h"

bool isBadVersion(int version);

int Solution278::firstBadVersion(int n) {
    unsigned long long start = 1;
    unsigned long long end = n;
    while (start < end) {
        unsigned long long error_version = (start + end) / 2;
        if (!isBadVersion(error_version)) {
            start = error_version + 1;
        } else {
            end = error_version;
        }
    }

    return start;
}

bool isBadVersion(int version) {
    return version >= 1;
}
