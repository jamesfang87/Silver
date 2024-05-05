#include <fstream>
#include <vector>
using namespace std;

int n;
vector<vector<char>> grid;
vector<vector<bool>> visited;
int cur_area;
int cur_perimeter;

void floodfill(int r, int c) {
    if ((r < 0 || r >= n + 2 || c < 0 || c >= n + 2)  // if out of bounds
        || grid[r][c] != '#'                // wrong color
        || visited[r][c])  // already visited this square
        return;

    visited[r][c] = true;  // mark current square as visited
    cur_area++;
    vector<pair<int, int>> neighbors = {{r, c + 1},
                                        {r, c - 1},
                                        {r - 1, c},
                                        {r + 1, c}};

    for (auto neighbor : neighbors) {
        if (neighbor.first < 0 ||
            neighbor.first >= n + 2 ||
            neighbor.second < 0 ||
            neighbor.second >= n + 2) {
            continue;
        }

        cur_perimeter += (grid[neighbor.first][neighbor.second] == '.');
    }

    // recursively call flood fill for neighboring squares
    floodfill(r, c + 1);
    floodfill(r, c - 1);
    floodfill(r - 1, c);
    floodfill(r + 1, c);
}

int main() {
    ifstream in("perimeter.in");
    ofstream out("perimeter.out");
    in >> n;
    grid = vector<vector<char>>(n + 2, vector<char>(n + 2, '.'));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            in >> grid[i][j];
        }
    }

    visited = vector<vector<bool>>(n + 2, vector<bool>(n + 2, false));

    int area_ans = INT32_MIN, perimeter_ans;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == '.')
                continue;

            if (visited[i][j])
                continue;

            cur_area = 0;
            cur_perimeter = 0;
            floodfill(i, j);

            if (cur_area > area_ans) {
                area_ans = cur_area;
                perimeter_ans = cur_perimeter;
            } else if (cur_area == area_ans && cur_perimeter < perimeter_ans) {
                area_ans = cur_area;
                perimeter_ans = cur_perimeter;
            }
        }
    }
    out << area_ans << ' ' << perimeter_ans;
}
