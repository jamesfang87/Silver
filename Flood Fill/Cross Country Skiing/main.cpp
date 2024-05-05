#include <fstream>
#include <vector>
#include <utility>
#include <cstring>
using namespace std;

const int MAX_SIZE = 500;
int grid[MAX_SIZE][MAX_SIZE];  // the grid itself
int row_num, col_num;
int visited[MAX_SIZE][MAX_SIZE];  // keeps track of which nodes have been visited

bool out_of_bounds(int r, int c) {
    return (r < 0 || r >= row_num || c < 0 || c >= col_num);
}

void floodfill(int r, int c, int max_diff) {
    if (visited[r][c] > 0)  // already visited this square
        return;

    visited[r][c]++;  // mark current square as visited

    // call flood fill for neighboring squares
    vector<pair<int, int>> neighbors = {{r, c + 1},
                                        {r, c - 1},
                                        {r - 1, c},
                                        {r + 1, c}};

    for (auto neighbor : neighbors) {
        if (out_of_bounds(neighbor.first, neighbor.second))
            continue;

        if (abs(grid[neighbor.first][neighbor.second] - grid[r][c]) <= max_diff)
            floodfill(neighbor.first, neighbor.second, max_diff);
    }
}

bool all_visited(const vector<pair<int, int>>& waypoints, int max_diff) {
    memset(visited, 0, sizeof visited);

    floodfill(waypoints[0].first, waypoints[0].second, max_diff);

    for (const auto & w : waypoints) {
        if (visited[w.first][w.second] == 0)
            return false;
    }
    return true;
}

int main() {
    ifstream in("ccski.in");
    ofstream out("ccski.out");

    in >> row_num >> col_num;
    for (int i = 0; i < row_num; i++) {
        for (int j = 0; j < col_num; j++) {
            in >> grid[i][j];
        }
    }

    vector<pair<int, int>> waypoints;
    for (int i = 0; i < row_num; i++) {
        for (int j = 0; j < col_num; j++) {
            int code; in >> code;
            if (code == 1) waypoints.emplace_back(i, j);
        }
    }

    int low = 0, high = 1000000001;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (all_visited(waypoints, mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    out << low;
}