#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> farthest;
vector<bool> visited;

void dfs(int cur) {
    if (visited[cur]) return;

    visited[cur] = true;
    //cout << "visited node " << cur << '\n';
    for (int neighbor : farthest[cur]) {
        dfs(neighbor);
    }
}

int main() {
    int n; cin >> n;
    farthest = vector<vector<int>>(n);
    for (int i = 0; i < n; i++) {
        int f; cin >> f; f--;

        farthest[f].push_back(i);
        farthest[i].push_back(f);
    }

    int component = 0;
    visited = vector<bool>(n, false);
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        
        //cout << "component " << component << ":\n";
        dfs(i); component++;
    }

    cout << component;
}
