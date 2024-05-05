#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<char>> grid;
vector<vector<bool>> visited;

void floodfill(int r, int c) {
    if ((r < 0 || r >= n || c < 0 || c >= m)  // if out of bounds
        || grid[r][c] != '.'                // wrong color
        || visited[r][c])  // already visited this square
        return;

    visited[r][c] = true;  // mark current square as visited

    // recursively call flood fill for neighboring squares
    floodfill(r, c + 1);
    floodfill(r, c - 1);
    floodfill(r - 1, c);
    floodfill(r + 1, c);
}

int main() {
    cin >> n >> m;
    grid = vector<vector<char>>(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    visited = vector<vector<bool>>(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
        }
    }

    int num_rooms = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#')
                continue;

            if (visited[i][j])
                continue;

            floodfill(i, j);
            num_rooms++;
        }
    }

    cout << num_rooms;
}
