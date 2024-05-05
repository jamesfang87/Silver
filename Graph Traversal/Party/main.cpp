#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

bool bfs(int p, vector<vector<int>>& adj) {
    int components = 0;
    vector<bool> seen(p, false);
    for (int i = 0; i < p; i++) {
        if (seen[i])
            continue;

        queue<int> q;
        q.push(i);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            seen[cur] = true;

            for (int j = 0; j < p; j++) {
                if (adj[cur][j] != 0 && !seen[j]) {
                    q.push(j);
                    seen[j] = true;
                }
            }
        }
        components++;
    }

    // return yes if james cannot invite everyone (so there is more than 1 component)
    return components > 1;
}

void solve(int p, int c) {
    vector<vector<int>> adj(p, vector<int>(p, 0));
    vector<pair<int, int>> connections(c);

    for (int i = 0; i < c; i++) {
        int a, b; cin >> a >> b;
        adj[a][b]++; adj[b][a]++;

        connections[i] = {a, b};
    }

    for (auto& connection : connections) {
        adj[connection.first][connection.second] = 0;
        adj[connection.second][connection.first] = 0;

        if (bfs(p, adj)) {
            cout << "YES\n";
            return;
        }

        adj[connection.first][connection.second] = 1;
        adj[connection.second][connection.first] = 1;
    }
    cout << "NO\n";
}

int main() {
    while (true) {
        int p, c; cin >> p >> c;
        if (p == 0 && c == 0) break;
        solve(p, c);
    }
}
