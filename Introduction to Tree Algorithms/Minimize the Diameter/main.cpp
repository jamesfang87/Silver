#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int furthest_node, max_dist;

vector<vector<int>> build_tree() {
    int n; cin >> n;
    vector<vector<int>> tree(n);
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    return tree;
}

void dfs(int src, int prev, int dist, const vector<vector<int>>& adj) {
    if (dist >= max_dist) {
        max_dist = dist;
        furthest_node = src;
    }
    
    for (int neighbor : adj[src]) {
        if (neighbor != prev) {
            dfs(neighbor, src, dist + 1, adj);
        }
    }
}

int diameter(const vector<vector<int>>& tree) {
    furthest_node = -1, max_dist = 0;
    dfs(0, -1, 0, tree);
    dfs(furthest_node, -1, 0, tree);
    return max_dist;
}

int main() {
    auto tree1 = build_tree(), tree2 = build_tree();
    int diameter1 = diameter(tree1), diameter2 = diameter(tree2);

    // let's first think about how we can maximize the diameter of a tree
    // to do so, we would connect one of the ends of each diameter
    // to create a new diameter of diameter1 + diameter2 + 1
    // to minimize the diameter instead, let's think about how we can adjust this
    // maximal diameter by minimizing the distance to all nodes
    // 
    // in any tree, the endpoint of the longest path starting from any node
    // will always be an endpoint of a diameter. however, unless the starting node
    // is the endpoint of the diameter, this value will always be less than the diameter
    // so we should try to place our node to minimize the effect of the diameter of the tree
    // thus, we should connect the midpoints of the diameters of the trees
    // from there we can do casework to see that we should round up in the case of odd diameters
    
    int ans = 1 + (diameter1 + 1) / 2 + (diameter2 + 1) / 2;
    // there might be a case where the original diameter of the two trees
    // is larger than ans: when diameter1 is 2 and diameter2 is some very large number
    cout << max({ans, diameter1, diameter2});
}