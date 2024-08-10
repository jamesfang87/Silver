#include <iostream>
#include <vector>
#include <utility>
using namespace std;

vector<vector<pair<int, int>>> adj;

int main() {
    int n, m; cin >> n >> m;

    adj = vector<vector<pair<int, int>>>(n);
    for (int i = 0; i < m; i++) {
        int a, b, color; cin >> a >> b >> color;
        adj[a].emplace_back(b, color);
    }


}
