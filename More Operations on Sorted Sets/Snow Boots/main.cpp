#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct Boot {
    int max_depth, max_step, index;
};

struct Tile {
    int depth, index;
};

bool cmp_tile(const Tile& a, const Tile& b) {
    return a.depth > b.depth;
}

bool cmp_boots(const Boot& a, const Boot& b) {
    return a.max_depth > b.max_depth;
}

int main() {
    /*
     * idea: we can think of this problem in a different theme:
     * farmer john has to carry a backpack with a certain weight (instead of boots)
     * and hop across a river on logs that can support a certain weight
     *
     * for each backpack, we can remove the logs that farmer john can't jump on
     * if the gap between two adjacent logs after this removal > the max distance fj can jump
     * then he can't make it to the other end of the river
     *
     * in this new scenario:
     * fj + backpack being too heavy is the same as the snow being too deep
     * fj being able to jump so far is the same as fj being able to stride so far in some boots
     *
     * to efficiently remove tiles fj can't step on,
     * we sort boots in order of decreasing amount of snow they can step into
     * thus, we don't have to re-remove tiles that we have already removed
     * for a boot with greater max depth
     *
     * we can also maintain a set of valid tiles, ones that fj can step into, and
     * a vector of all the tiles
     *
     * we can also sort tiles in order of decreasing depth to speed this up:
     * we start at the deepest tile and tiles from the set of valid tiles
     * until all tiles are valid in valid tiles
     */
    ifstream cin("snowboots.in");
    ofstream cout("snowboots.out");
    int n, b; cin >> n >> b;

    vector<Tile> tiles(n);
    for (int i = 0; i < n; i++) {
        int depth; cin >> depth;
        tiles[i] = {depth, i};
    }
    sort(tiles.begin(), tiles.end(), cmp_tile);

    set<int> valid_tiles;
    for (int i = 0; i < n; i++) {
        valid_tiles.insert(i);
    }

    vector<Boot> boots(b);
    for (int i = 0; i < b; i++) {
        cin >> boots[i].max_depth >> boots[i].max_step;
        boots[i].index = i;
    }
    sort(boots.begin(), boots.end(), cmp_boots);

    auto tile_ptr = tiles.begin(); // tile_ptr, points to a tile
    int biggest_gap = 1; // biggest gap between two adj tiles after removals

    vector<bool> ans(b);
    for (const Boot& boot : boots) {
        // in range && can't traverse because depth at a tile > max depth of boot
        while (tile_ptr < tiles.end() && tile_ptr->depth > boot.max_depth) {
            auto remove = valid_tiles.find(tile_ptr->index);

            // tiles that will be adj after removal
            int before_tile = *prev(remove), after_tile = *next(remove);
            biggest_gap = max(biggest_gap, after_tile - before_tile);

            valid_tiles.erase(remove);
            tile_ptr++;
        }
        ans[boot.index] = boot.max_step >= biggest_gap;
    }

    for (int a : ans) {
        cout << a << '\n';
    }
}