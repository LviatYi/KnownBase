#include "Sword13.h"

#pragma region 直接计算
static int blockFlood(int x, int y, int waterPower, int mBorder, int nBorder) {
    if (waterPower - x - y < 8 && !(x == 0 && y == 0)) {
        return 0;
    }

    mBorder = mBorder >= (x + 1) * 10 ? 10 : mBorder % 10;
    nBorder = nBorder >= (y + 1) * 10 ? 10 : nBorder % 10;

    waterPower = (waterPower - (x + y));

    int sum = 0;
    for (int i = 0; i < nBorder && waterPower - i >= 0; i++) {
        sum += (waterPower - i) + 1 < mBorder ? (waterPower - i) + 1 : mBorder;
    }

    return sum;
}

int Sword13::movingCount(int m, int n, int k) {
    int sum = 0;

    for (int i = 0; i - 1 < m / 10; i++) {
        for (int j = 0; j - 1 < n / 10; j++) {
            int currSum = blockFlood(i, j, k, m, n);
            if (currSum == 0) {
                break;
            }
            else {
                sum += currSum;
            }
        }
    }

    return sum;
}
#pragma endregion

#pragma region DFS
static int res = 0;
static bool visited[100][100];

static void dfs(int x, int y, int m, int n, int k) {
    if (x == m || y == n || visited[x][y]) {
        return;
    }
    int sum = x % 10 + y % 10 + x / 10 + y / 10;
    if (sum > k) {
        return;
    }
    visited[x][y] = true;
    res++;
    dfs(x + 1, y, m, n, k);
    dfs(x, y + 1, m, n, k);
}
int Sword13::movingCount2(int m, int n, int k) {
    dfs(0, 0, m, n, k);
    return res;
}
#pragma endregion

