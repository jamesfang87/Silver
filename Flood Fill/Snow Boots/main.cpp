#include <bits/stdc++.h>
using namespace std;

int n, b;
vector<int> tiles;
vector<pair<int, int>> boots; // .first = max depth .second = max step
bool visited[251][251];
int ans = 250;

void search(int cur_tile, int cur_boot, int boots_discarded) {
    if (visited[cur_tile][cur_boot]) {
        return;
    }

    if (cur_tile + boots[cur_boot].second >= n - 1) {
        ans = min(ans, boots_discarded);
        return;
    }

    visited[cur_tile][cur_boot] = true;

    // explore options where farmer john doesn't discard any boots
    int max_depth = boots[cur_boot].first;
    int max_step = boots[cur_boot].second;
    int furthest_distance = min(n - 1, cur_tile + max_step);
    for (int new_tile = cur_tile + 1; new_tile <= furthest_distance; new_tile++) {
        if (tiles[new_tile] > max_depth) {
            continue;
        }
        search(new_tile, cur_boot, boots_discarded);
    }

    // explore when farmer john discards boots
    int newly_discarded = boots_discarded;
    for (int new_boot = cur_boot + 1; new_boot < b; new_boot++) {
        newly_discarded++;
        if (tiles[cur_tile] > boots[new_boot].first) {
            continue;
        }
        search(cur_tile, new_boot, new_boot);
    }
}

int main() {
    ifstream fin("snowboots.in");
    ofstream fout("snowboots.out");

    fin >> n >> b;

    for (int i = 0; i < n; i++) {
        int temp; fin >> temp;
        tiles.push_back(temp);
    }

    for (int i = 0; i < b; i++) {
        int max_depth, max_step;
        fin >> max_depth >> max_step;
        boots.emplace_back(max_depth, max_step);
    }

    memset(visited, false, sizeof visited);
    search(0, 0, 0);
    fout << ans;
}
