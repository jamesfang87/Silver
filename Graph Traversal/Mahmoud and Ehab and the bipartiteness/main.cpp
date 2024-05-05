#include <vector>
#include <iostream>
using namespace std;

int n;
vector<vector<int>> adj;
int color[100000];
int blue = 0, red = 0;

void dfs(int cur) {
    int opposite_color = ! (bool) color[cur];
    for (int neighbor : adj[cur]) {
        if (color[neighbor] == -1) {
            color[neighbor] = opposite_color;
            if (opposite_color == 0)
                blue++;
            else
                red++;
            dfs(neighbor);
        }
    }
}

int main() {
    cin >> n;
    adj = vector<vector<int>>(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }


    memset(color, -1, sizeof color);
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0; blue++;
            dfs(i);
        }
    }


    cout << (long long) red * blue - (n - 1);
}
