#include "Solution37.h"
#include<array>

using namespace std;

#pragma region 回溯 位标记法 桶
array<int, 9> xLine{ 0 };
array<int, 9> yLine{ 0 };
array<array<int, 3>, 3> box{ 0 };

bool insertSudoku(vector<vector<char>>& board, int i, int j) {
    if (j >= 9) {
        i += j / 9;
        j %= 9;
    }
    if (i >= 9) {
        return true;
    }

    if (board[i][j] != '.') {
        // 填入下一位
        return insertSudoku(board, i, j + 1);
    }

    int insertNum = 1;
    for (; insertNum <= 9; insertNum++) {

        int judge = 1 << insertNum;

        if (xLine[i] & judge || yLine[j] & judge || box[i / 3][j / 3] & judge) {
            continue;
        }
        else {
            board[i][j] = insertNum + '0';
            yLine[j] += judge;
            xLine[i] += judge;
            box[i / 3][j / 3] += judge;
            if (insertSudoku(board, i, j + 1)) {
                return true;
            }
            else {
                yLine[j] -= judge;
                xLine[i] -= judge;
                box[i / 3][j / 3] -= judge;
                continue;
            }
        }
    }

    if (insertNum > 9) {
        board[i][j] = '.';
        // 插入失败
        return false;
    }
    else {
        return insertSudoku(board, i, j + 1);
    }
}

void Solution37::solveSudoku(vector<vector<char>>& board) {
    bool isValid = true;

    // load in
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
                int k = 1 << board[i][j] - '0';
                yLine[j] += k;
                xLine[i] += k;
                box[i / 3][j / 3] += k;
            }
        }
    }

    insertSudoku(board, 0, 0);

    return;
}
#pragma endregion
