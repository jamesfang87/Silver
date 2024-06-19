#include <iostream>
#include <vector>
#include <set>
using namespace std;

string maze[25][25];
bool visited[25][25][19683];
int powers_of_3[10];
set<int> valid_winning_boards;

struct Board {
    int hash;

    explicit Board(int h) {
        hash = h;
    }

    int get(int index) const {
       return hash / powers_of_3[index] % 3;
    }

    void set(int index, int new_val) {
        hash += new_val * powers_of_3[index];
    }

    vector<int> to_vec() const {
        vector<int> board(9);
        for (int i = 0; i < 9; i++) {
            board[i] = get(i);
        }
        return board;
    }
};

bool winning_state(const vector<int>& board) {
    vector<int> valid1 = {1, 1, 2};
    vector<int> valid2 = {2, 1, 1};

    for (int r = 0; r < 3; r++) {
        vector<int> row; row.reserve(3);
        for (int pos = r * 3; pos < r * 3 + 3; pos++) {
            row.push_back(board[pos]);
        }

        if (row == valid1 || row == valid2) {
            return true;
        }
    }

    for (int c = 0; c < 3; c++) {
        vector<int> col; col.reserve(3);
        for (int pos = c; pos < 9; pos += 3) {
            col.push_back(board[pos]);
        }

        if (col == valid1 || col == valid2) {
            return true;
        }
    }

    vector<int> diagonal = {board[0], board[4], board[8]};
    if (diagonal == valid1 || diagonal == valid2) {
        return true;
    }

    vector<int> r_diagonal = {board[2], board[4], board[6]};
    if (r_diagonal == valid1 || r_diagonal == valid2) {
        return true;
    }

    return false;
}


void floodfill(int r, int c, Board board) {
    if (visited[r][c][board.hash] || maze[r][c][0] == '#') {
        return;
    }

    visited[r][c][board.hash] = true;

    // check to see what we have to do
    string temp = maze[r][c];
    if (temp[0] == 'M' || temp[0] == 'O') {
        int affected_row = temp[1] - '1', affected_col = temp[2] - '1';

        // convert to format for board: tic-tac-toe board is flattened and M = 2; O = 1
        int board_index = affected_row * 3 + affected_col;
        int new_val = (temp[0] == 'M') + 1;

        // if that cell in the board is unfilled
        if (board.get(board_index) == 0) {
            board.set(board_index, new_val);
            // insert to set of valid winning boards if we haven't already
            if (!visited[r][c][board.hash] && winning_state(board.to_vec())) {
                valid_winning_boards.insert(board.hash);
                // bessie stops right as she wins in cow tic-tac-toe
                return;
            }
            visited[r][c][board.hash] = true;
        }
    }

    // move to neighbors
    floodfill(r + 1, c, board);
    floodfill(r - 1, c, board);
    floodfill(r, c + 1, board);
    floodfill(r, c - 1, board);
}

int main() {
    // pre-compute powers of 3 up to 3^9
    int result = 1;
    for (int & i : powers_of_3) {
        i = result;
        result *= 3;
    }

    pair<int, int> bessie_pos;

    // input
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string line; cin >> line;
        for (int j = 0; j < n; j++) {
            maze[i][j] = line.substr(j * 3, 3);

            if (maze[i][j][0] == 'B') {
                bessie_pos = {i, j};
            }
        }
    }

    auto cur_board = Board(0);
    floodfill(bessie_pos.first, bessie_pos.second, cur_board);
    cout << valid_winning_boards.size() << '\n';
}
