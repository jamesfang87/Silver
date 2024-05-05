#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<int> color;

bool dfs(int cur) {
    int cur_color = color[cur];
    int opposite = ! (bool) cur_color;

    for (int neighbor : adj[cur]) {
        if (color[neighbor] != -1) {
            if (cur_color == color[neighbor]) {
                return false;
            }
        } else {
            color[neighbor] = opposite;
            if (!dfs(neighbor)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
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
            if (!dfs(i)) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << color[i] + 1 << " \n"[i == n - 1];
    }
}
