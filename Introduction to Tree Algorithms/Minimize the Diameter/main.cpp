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

    //to the see best nodes to connect, we can first do some casework, 
    //distinguishing nodes into categories: on the diameter and off the diameter.

    // for nodes off the diameter, the longest path will end at an endpoint of the diameter,
    // specifically the endpoint further away from the node that the path meets the diameter at. 
    // this length consists of the length of the path to the diameter 
    // and the path from the aforementioned node to the further endpoint, 
    // which has a distance of at least half of the diameter. 
    // if we are forced to connect nodes that are off the diameter,
    // we can see that we should choose ones closer to the diameter 
    // and enter the diameter at a place close to the middle.

    // if we connect to a node on the diameter, we skip the path to the diameter 
    // and instead travel the distance to the furthest endpoint. 
    // thus, the optimal solution is to connect the two midpoints of the two diameters.
    
    int ans = 1 + (diameter1 + 1) / 2 + (diameter2 + 1) / 2;
    // there might be a case where the original diameter of the two trees
    // is larger than ans: when diameter1 is 2 and diameter2 is some very large number
    cout << max({ans, diameter1, diameter2});
}