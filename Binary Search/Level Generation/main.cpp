#include <cstdint>
#include <iostream>
using namespace std;

bool possible(int edges, int nodes) {
    int bridges = (edges + 1) / 2;
    int edges_left = edges - bridges;
    
    int free_nodes = nodes;
    return edges_left <= (free_nodes - 1) * free_nodes / 2;
}

int solve() {
    int n; cin >> n;
    
    int l = 0, r = INT32_MAX - 1;
    while (l < r) {
        int m = l + (r - l + 1) / 2;
        if (possible(m, n)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q; cin >> q;
    while (q--) {
        cout << solve() << '\n';
    }
}