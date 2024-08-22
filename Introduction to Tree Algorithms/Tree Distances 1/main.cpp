#include <iostream>
#include <vector>
using namespace std;

int furthest_node, max_dist;
vector<vector<int>> adj;



void dfs(int src, int prev, int dist) {
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


pair<int, int> diameter(const vector<vector<int>>& tree) {
    // .first is the first endpoint of the diameter
    // .second is the second endpoint of the diameter
    pair<int, int> endpoints; 
    furthest_node = -1, max_dist = 0;

    dfs(0, -1, 0, tree);
    endpoints.first = furthest_node;
    
    dfs(furthest_node, -1, 0, tree);
    endpoints.second = furthest_node;

    return endpoints;
}

int main() {
    int n; cin >> n;
    adj = vector<vector<int>>(n);
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }


}