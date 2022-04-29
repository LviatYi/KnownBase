#include "Solution36.h"
#include <array>
#include <cctype>
using namespace std;

#pragma region 位标记法 + 桶
bool Solution36::isValidSudoku(vector<vector<char>>& board) {
    bool isValid = true;
    array<int, 9> xLine{ 0 };
    array<int, 9> yLine{ 0 };
    array<array<int, 3>, 3> box{ 0 };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
                int k = 1 << board[i][j] - '0';
                if (xLine[i] & k || yLine[j] & k || box[i / 3][j / 3] & k) {
                    isValid = false;
                    break;
                }
                else {
                    yLine[j] += k;
                    xLine[i] += k;
                    box[i / 3][j / 3] += k;
                }
            }
            if (!isValid) {
                break;
            }
        }
    }

    return isValid;
}
#pragma endregion

