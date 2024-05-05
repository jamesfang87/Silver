#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
using namespace std;

vector<unordered_set<int>> not_adj;
vector<int> component_sizes;
set<int> unvisited;
int component_size = 0;

void dfs(int cur) {
    // increase size of current component
    component_size++;

    // loop through all unvisited neighbors
    auto node = unvisited.begin();
    while (node != unvisited.end()) {
        if (not_adj[cur].count(*node) == 0) {
            int neighbor = *node;
            // remove node from the set of unvisited nodes
            unvisited.erase(node);
            // call dfs on node (which we know is a neighbor)
            dfs(neighbor);

            // get the next node
            node = unvisited.upper_bound(neighbor);
        } else {
            // skip the current node if there is no edge
            node++;
        }
    }
}

int main() {
    int n, m; cin >> n >> m;
    not_adj = vector<unordered_set<int>>(n);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        not_adj[a].insert(b);
        not_adj[b].insert(a);
    }

    for (int i = 0; i < n; i++)
        unvisited.insert(i);

    int cur_component = 0;
    for (int i = 0; i < n; i++) {
        auto it = unvisited.find(i);
        if (it != unvisited.end()) {
            unvisited.erase(it);
            // dfs
            dfs(i);

            // resets and other stuff
            component_sizes.push_back(component_size);
            component_size = 0;
            cur_component++;
        }
    }

    sort(component_sizes.begin(), component_sizes.end());
    cout << cur_component << '\n';
    for (const int& s : component_sizes) {
        cout << s << ' ';
    }
}
