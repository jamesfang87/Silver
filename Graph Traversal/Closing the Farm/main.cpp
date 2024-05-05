#include <vector>
#include <fstream>
#include <queue>
using namespace std;

int num_connected_groups(int n, vector<bool> valid, const vector<vector<int>>& adj) {
    int connected = 0;
    for (int i = 0; i < n; i++) {
        if (!valid[i]) continue;

        connected++;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int current_barn = q.front();
            q.pop();
            
            valid[current_barn] = false;
            
            for (int neighbor : adj[current_barn]) {
                if (valid[neighbor])
                    q.push(neighbor);
            }
        }
    }
    return connected;
}

int main() {
    ifstream fin("closing.in");
    ofstream fout("closing.out");
    int n, m; fin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int node1, node2; fin >> node1 >> node2;
        node1--; node2--;
        adj[node1].push_back(node2);
        adj[node2].push_back(node1);
    }
    
    vector<bool> valid(n, true);
    
    for (int i = 0; i < n; i++) {
        if (num_connected_groups(n, valid, adj) == 1)
            fout << "YES\n";
        else
            fout << "NO\n";
        
        int closed; fin >> closed;
        
        valid[--closed] = false;
        adj[closed] = {};
    }
}