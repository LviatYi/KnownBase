#include <iostream>
#include <vector>

using namespace std;

const int board_size = 9;

int get_cell_index(int row, int col) {
    return row / 3 * 3 + col / 3;
}

bool valid(int flag,
           int i,
           int j,
           std::vector<int>& row_board_state,
           std::vector<int>& col_board_state,
           std::vector<int>& cell_board_state) {
    int f = 1 << (flag - 1);
    return !(row_board_state[i] & f) &&
        !(col_board_state[j] & f) &&
        !(cell_board_state[get_cell_index(i, j)] & f);
}

void record_for_row(std::vector<int>& row_board_state, int i, int k) {
    row_board_state[i] |= 1 << (k - 1);
}

void record_for_col(std::vector<int>& col_board_state, int j, int k) {
    col_board_state[j] |= 1 << (k - 1);
}

void record_for_cell(std::vector<int>& cell_board_state, int i, int j, int k) {
    cell_board_state[get_cell_index(i, j)] |= 1 << (k - 1);
}

void erase_for_row(std::vector<int>& row_board_state, int i, int k) {
    row_board_state[i] &= ~(1 << (k - 1));
}

void erase_for_col(std::vector<int>& col_board_state, int j, int k) {
    col_board_state[j] &= ~(1 << (k - 1));
}

void erase_for_cell(std::vector<int>& cell_board_state, int i, int j, int k) {
    cell_board_state[get_cell_index(i, j)] &= ~(1 << (k - 1));
}

bool dfs(std::vector<std::vector<int>>& board,
         std::vector<int>& row_board_state,
         std::vector<int>& col_board_state,
         std::vector<int>& cell_board_state) {
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            if (board[i][j] == 0) {
                for (int k = 1; k <= board_size; ++k) {
                    if (valid(k,
                              i,
                              j,
                              row_board_state,
                              col_board_state,
                              cell_board_state)) {
                        board[i][j] = k;
                        record_for_row(row_board_state, i, k);
                        record_for_col(col_board_state, j, k);
                        record_for_cell(cell_board_state, i, j, k);

                        if (dfs(board,
                                row_board_state,
                                col_board_state,
                                cell_board_state)) {
                            return true;
                        } else {
                            erase_for_row(row_board_state, i, k);
                            erase_for_col(col_board_state, j, k);
                            erase_for_cell(cell_board_state, i, j, k);
                        }
                    }
                }
                board[i][j] = 0;
                return false;
            }
        }
    }

    return true;
}

int hj44() {
    std::vector<std::vector<int>> board(board_size,
                                        std::vector<int>(board_size));

    std::vector row_board_state(board_size, 0);
    std::vector col_board_state(board_size, 0);
    std::vector cell_board_state(board_size, 0);

    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            int val;
            std::cin >> val;
            board[i][j] = val;
            if (val > 0) {
                record_for_row(row_board_state, i, val);
                record_for_col(col_board_state, j, val);
                record_for_cell(cell_board_state, i, j, val);
            }
        }
    }

    dfs(board, row_board_state, col_board_state, cell_board_state);

    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
