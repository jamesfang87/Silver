#include <fstream>
#include <utility>
#include <vector>
#include <set>
#include <map>
using namespace std;

// global vars
int n, k, r;
const int MAX_N = 101;
int farm[MAX_N][MAX_N];
map<pair<int, int>, set<pair<int, int>>> roads;
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

void floodfill(int row, int col, int component_num) {
    if ((row < 1 || row > n || col < 1 || col > n) || farm[row][col] > 0)
        return;

    farm[row][col] = component_num;

    for (int i = 0; i < 4; i++) {
        int new_row = dr[i] + row;
        int new_col = dc[i] + col;

        set<pair<int, int>> temp = roads[{row, col}];
        if (temp.find({new_row, new_col}) == temp.end()) {
            // flood fill if there is no road between two fields
            floodfill(new_row, new_col, component_num);
        }
    }
}

int main() {
    ifstream fin("countcross.in");
    ofstream fout("countcross.out");

    fin >> n >> k >> r;
    for (int i = 0; i < r; i++) {
        int r1, c1, r2, c2;
        fin >> r1 >> c1 >> r2 >> c2;

        roads[{r1, c1}].insert({r2, c2});
        roads[{r2, c2}].insert({r1, c1});
    }
    
    vector<pair<int, int>> cow_locations(k);
    for (auto& location : cow_locations) {
        fin >> location.first >> location.second;
    }

    // flood fill
    int component_num = 1;
    for (auto location : cow_locations) {
        if (farm[location.first][location.second] == 0) {
            floodfill(location.first, location.second, component_num);
            component_num++;
        }
    }

    // examine pairs
    vector<int> cow_components(k);
    for (int i = 0; i < k; i++) {
        cow_components[i] = farm[cow_locations[i].first][cow_locations[i].second];
    }

    int ans = 0;
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (cow_components[i] != cow_components[j]) {
                ans++;
            }
        }
    }
    fout << ans;
}
