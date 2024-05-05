#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<int> color;
int blue = 0, red = 0;

void dfs(int cur) {
    int cur_color = color[cur];
    int opposite = ! (bool) cur_color;

    for (int neighbor : adj[cur]) {
        if (color[neighbor] == -1) {
            color[neighbor] = opposite;
            if (opposite == 0)
                blue++;
            else
                red++;
            dfs(neighbor);
        }
    }
}

void solve() {
    int n, m; cin >> n >> m;
    adj = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    color = vector<int>(n, -1);
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            blue = 1; red = 0;

            dfs(i);
        }
    }

    if (blue < red) {
        cout << blue << '\n';
        for (int i = 0; i < n; i++) {
            if (color[i] == 0) cout << i + 1 << ' ';
        }
    } else {
        cout << red << '\n';
        for (int i = 0; i < n; i++) {
            if (color[i] == 1) cout << i + 1 << ' ';
        }
    }
    cout << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
