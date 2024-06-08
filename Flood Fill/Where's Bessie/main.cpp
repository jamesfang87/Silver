#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

char field[20][20];
bool visited[20][20];
int min_r = 0, min_c = 0;
int max_r = 0, max_c = 0;
int components_of[26];
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

struct PCL {
    int r1, c1, r2, c2;

    bool is_inside(PCL other) const {
        return (r1 >= other.r1 && r2 <= other.r2 && c1 >= other.c1 && c2 <= other.c2);
    }
};

void floodfill(int r, int c, char color) {
    if ((r < min_r || r > max_r || c < min_c || c > max_c)
        || visited[r][c]
        || field[r][c] != color) {
        return;
    }

    visited[r][c] = true;
    for (int i = 0; i < 4; i++) {
        floodfill(r + dr[i], c + dc[i], color);
    }
}

void reset() {
    memset(visited, false, sizeof visited);
    memset(components_of, 0, sizeof components_of);
}

bool is_pcl() {
    int unique_colors = 0;
    bool criteria1 = false;
    bool criteria2 = false;
    for (int components : components_of) {
        if (components > 0) {
            unique_colors++;
        }
        // one of the two colors must have only 1 component
        if (components == 1) {
            criteria1 = true;
        }
        // the other color must have 2 or more components
        if (components >= 2) {
            criteria2 = true;
        }
    }

    // check that we only have 2 unique colors first
    if (unique_colors != 2) {
        return false;
    }

    // check criteria 1 and 2
    if (criteria1 && criteria2) {
        return true;
    }

    return false;
}

bool search() {
    for (int r = min_r; r <= max_r; r++) {
        for (int c = min_c; c <= max_c; c++) {
            if (visited[r][c]) {
                continue;
            }

            floodfill(r, c, field[r][c]);
            components_of[field[r][c] - 'A']++;
        }
    }

    bool temp = is_pcl();
    reset();
    return temp;
}

int main() {
    ifstream fin("where.in");
    ofstream fout("where.out");
    int n; fin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> field[i][j];
        }
    }

    vector<PCL> pcls;
    for (min_r = 0; min_r < n; min_r++) {
        for (min_c = 0; min_c < n; min_c++) {
            for (max_r = n - 1; max_r >= 0; max_r--) {
                for (max_c = n - 1; max_c >= 0; max_c--) {
                    if (search()) {
                        pcls.push_back({min_r, min_c, max_r, max_c});
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < pcls.size(); i++) {
        bool valid_pcl = true;
        for (int j = 0; j < pcls.size(); j++) {
            if (i == j) {
                continue;
            }

            if (pcls[i].is_inside(pcls[j])) {
                valid_pcl = false;
                break;
            }
        }

        if (valid_pcl) {
            ans++;
        }
    }

    fout << ans;
}