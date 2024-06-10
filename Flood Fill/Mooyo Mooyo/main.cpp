#include <fstream>
#include <limits>
#include <utility>
#include <vector>
#include <cstring>

int n, k;
const int MAX_N = 100;
int grid[MAX_N][10];
bool visited[MAX_N][10];
std::vector<std::pair<int, int> > cur_component;
int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

bool out_of_range(int r, int c) {
    return (r >= n || r < 0 || c >= 10 || c < 0);
}

void floodfill(int r, int c) {
    if (out_of_range(r, c) || visited[r][c] || grid[r][c] == 0) {
        return;
    }

    visited[r][c] = true;
    cur_component.emplace_back(r, c);

    for (int i = 0; i < 4; i++) {
        // if the color of the neighboring cell is the same, travel to it
        if (grid[r + dr[i]][c + dc[i]] == grid[r][c]) {
            floodfill(r + dr[i], c + dc[i]);
        }
    }
}

// removes components of haybales if they have size of k or more
// returns true if haybales were removed, false otherwise
bool remove_haybales() {
    bool removed = false;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < 10; c++) {
            if (visited[r][c] || grid[r][c] == 0)
                continue;

            // floodfill to find connected component
            floodfill(r, c);
            // remove component if it has k or more haybales
            if (cur_component.size() >= k) {
                removed = true;
                for (std::pair<int, int> haybale : cur_component) {
                    grid[haybale.first][haybale.second] = 0;
                }
            }

            cur_component.clear();
        }
    }
    memset(visited, false, sizeof visited);
    return removed;
}

int main() {
    std::ifstream fin("mooyomooyo.in");
    std::ofstream fout("mooyomooyo.out");

    fin >> n >> k;
    for (int i = 0; i < n; i++) {
        std::string line; fin >> line;
        for (int j = 0; j < 10; j++) {
            grid[i][j] = line[j] - '0';
        }
    }

    while (remove_haybales()) {
        for (int c = 0; c < 10; c++) {
            int first_zero_location = 0;
            for (int r = n - 1; r >= 0; r--) {
                if (grid[r][c] == 0) {
                    first_zero_location = r;
                    break;
                }
            }

            int falls_to = first_zero_location;
            for (int r = first_zero_location - 1; r >= 0; r--) {
                if (grid[r][c] != 0) {
                    grid[falls_to][c] = grid[r][c];
                    grid[r][c] = 0;
                    falls_to--;
                }
            }
        }
    }

    // output grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            fout << grid[i][j];
        }
        fout << '\n';
    }
}
