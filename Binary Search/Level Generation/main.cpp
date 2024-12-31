#include <cstdint>
#include <iostream>
using namespace std;

bool possible(long long total_edges, long long nodes) {
    long long bridges_needed = (total_edges + 1) / 2;
    long long edges_left = total_edges - bridges_needed;

    if (nodes < bridges_needed) {
        return false;
    }

    long long free_nodes = nodes - bridges_needed;
    return edges_left <= (free_nodes - 1) * free_nodes / 2;
}

long long solve() {
    // an easy (and sneaky) way to cheat the problem is
    // create a tree with depth 1 rooted at some arbitrary node
    // then, the number of nodes in the tree is 1 + the number of bridges needed
    // basically, if you need 2 bridges and you choose node 1 as your root,
    // then your tree looks 1 - 2 and 1 - 3. then, the rest of the nodes
    // are connected to the root.
    int n;
    cin >> n;

    // be sure to properly handle the edge case of n = 1,
    // since this way doesn't really work with just 1 node
    if (n == 1) {
        return 0;
    }

    long long l = -1, r = INT64_MAX;
    while (l < r) {
        long long m = l + (r - l + 1) / 2;
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

    int q;
    cin >> q;
    while (q--) {
        cout << solve() << '\n';
    }
}
