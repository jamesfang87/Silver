#include <iostream>
#include <vector>
#include <cstring>
#include <utility>
using namespace std;

const int MAX_N = 50, MAX_M = 50;
char grid[MAX_N + 2][MAX_M + 2];
bool visited[MAX_N + 2][MAX_M + 2];
int n, m;

void floodfill(int r, int c) {
    if (visited[r][c] || grid[r][c] == '#')  // already visited this square
        return;

    visited[r][c] = true;  // mark current square as visited

    // call flood fill for neighboring squares
    floodfill(r, c + 1);
    floodfill(r, c - 1);
    floodfill(r - 1, c);
    floodfill(r + 1, c);
}

void solve() {
    memset(grid, '.', sizeof grid);
    memset(visited, true, sizeof visited);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            visited[i][j] = false;
        }
    }

    pair<int, int> directions[4] = {{0, 1},
                                    {0, -1},
                                    {1, 0},
                                    {-1, 0}};

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] != 'B') {
                continue;
            }

            for (auto d : directions) {
                if (grid[i + d.first][j + d.second] == 'G') {
                    cout << "No\n";
                    return;
                } else if (grid[i + d.first][j + d.second] == '.') {
                    grid[i + d.first][j + d.second] = '#';
                }
            }
        }
    }

    floodfill(n, m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == 'G' && !visited[i][j]) {
                 cout << "No" << '\n';
                 return;
            }
        }
    }

    cout << "Yes" << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
