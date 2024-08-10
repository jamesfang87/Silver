#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<bool> visited(n, false);

    for (int i = 0; i < m; i++) {
        int city1, city2; cin >> city1 >> city2;
        city1--; city2--;
        adj[city1].push_back(city2);
        adj[city2].push_back(city1);
    }

    int ans = -1;
    vector<int> connected_components;
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        queue<int> q;
        q.push(i);
        connected_components.push_back(i);
        ans++;

        while (!q.empty()) {
            int cur_city = q.front();
            q.pop();
            visited[i] = true;

            for (int neighbor : adj[cur_city]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
    cout << ans << '\n';
    for (int i = 0; i < ans; i++) {
        cout << connected_components[i] + 1 << ' ' << connected_components[i + 1] + 1 << '\n';
    }
   
}
