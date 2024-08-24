#include <iostream>
#include <vector>
using namespace std;

int dist_to_endpoints[200000][2];
int furthest_node, max_dist;
vector<vector<int>> adj;

void dfs(int src, int prev, int dist, int endpoint) {
    // if we see a node that is further away than 
    // ones we've seen before, set it as the furthest node
    if (dist >= max_dist) {
        max_dist = dist;
        furthest_node = src;
    }

    if (endpoint > -1) {
        dist_to_endpoints[src][endpoint] = dist;
    }
    
    for (int neighbor : adj[src]) {
        if (neighbor != prev) {
            dfs(neighbor, src, dist + 1, endpoint);
        }
    }
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

    // the maximum distance from any node in a tree is 
    // one of the endpoints of the diameter
    // we can run 2 dfs's to find the endpoints of the diameter, a and b
    dfs(0, -1, 0, -1);
    int endpointA = furthest_node;

    // in the second dfs, which starts at an endpoint
    // we can assign distances for that endpoint
    dfs(endpointA, -1, 0, 0);
    int endpointB = furthest_node;

    // then we run one last dfs on the 2nd endpoint
    // assigning distances as we go
    dfs(endpointB, -1, 0, 1);

    // then for each node, output max(dist(a), dist(b))
    for (int i = 0; i < n; i++) {
        int dist = max(dist_to_endpoints[i][0], dist_to_endpoints[i][1]);
        printf("%d ", dist);
    }
}