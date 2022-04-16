#include "Sword64.h"

/**
 * \brief 
 * \param n 
 * \return 
 */
int Sword64::sumNums(int n) {
    int ans = 1;
    (n == 1) || (ans = n + sumNums(n - 1));
    return ans;
}

// int Sword64::sumNums2(int n) {
//     return sizeof(bool[n][n + 1]) >> 1;
// }
