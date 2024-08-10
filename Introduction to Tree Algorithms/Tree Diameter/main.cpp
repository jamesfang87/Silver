#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int> > adj;
int max_dist = 0;
int furtest_node = 0;

void dfs(int src, int prev, int dist) {
    //cout << "visited node " << src << "with dist " << dist << '\n';
    // process node
    if (dist >= max_dist) {
        max_dist = dist;
        furtest_node = src;
    }
    
    for (int neighbor : adj[src]) {
        if (neighbor != prev) {
            dfs(neighbor, src, dist + 1);
        }
    }
}

int main() {
    cin >> n;
    adj = vector<vector<int> >(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    dfs(1, 0, 0);
    dfs(furtest_node, -1, 0);
    cout << max_dist;
}
