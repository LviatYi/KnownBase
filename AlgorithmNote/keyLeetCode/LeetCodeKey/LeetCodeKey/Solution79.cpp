#include "Solution79.h"

static int rows, cols;
static string target;

bool isMatch(vector<vector<char>>& board, int x, int y, string& word, int matchCount) {
    if (matchCount >= word.size()) {
        return true;
    }
    if (x < 0 ||
        x >= rows ||
        y < 0 ||
        y >= cols ||
        board[x][y] != word[matchCount]) {
        // 越界
        return false;
    }
    else {
        bool isMatched = false;
        board[x][y] = 0;

        isMatched = isMatch(board, x - 1, y, word, matchCount + 1)
            || isMatch(board, x + 1, y, word, matchCount + 1)
            || isMatch(board, x, y + 1, word, matchCount + 1)
            || isMatch(board, x, y - 1, word, matchCount + 1);

        board[x][y] = word[matchCount];
        return isMatched;
    }
}

bool Solution79::exist(vector<vector<char>>& board, string word) {
    rows = board.size();
    cols = board[0].size();
    vector<vector <bool>> visited(rows, vector<bool>(cols, false));
    int matchCount = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (isMatch(board, i, j, word, 0)) {
                return true;
            }
        }
    }
    return false;
}