#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<bool> cyclic;

void in_cycle(int start, vector<int> path) {
    if (!path.empty() && start == path[0]) {
        for (int node : path) cyclic[node] = true;
        return;
    }

    path.push_back(start);

    for (int neighbor : adj[start]) {
        if (visited[neighbor]) continue;

        visited[neighbor] = true;
        in_cycle(neighbor, path);
    }
}

int main() {
    int n, k; cin >> n >> k;

    adj = vector<vector<int>>(n);
    for (int i = 0; i < k; i++) {
        int a, b, score_a, score_b; cin >> a >> b >> score_a >> score_b;
        a--; b--;

        if (score_a > score_b)
            adj[b].push_back(a);
        else
            adj[a].push_back(b);
    }

    cyclic = vector<bool>(n, false);
    for (int i = 0; i < n; i++) {
        if (!cyclic[i]) {
            visited = vector<bool>(n, false);
            in_cycle(i, {});
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += cyclic[i];

    cout << ans;
}


/*
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

bool in_cycle(int start, vector<int> path) {
    if (!path.empty() && start == path[0]) return true;

    path.push_back(start);

    for (int neighbor : adj[start]) {
        if (visited[neighbor]) continue;

        visited[neighbor] = true;
        if (in_cycle(neighbor, path))
            return true;
    }
    return false;
}

int main() {
    int n, k; cin >> n >> k;

    adj = vector<vector<int>>(n);
    for (int i = 0; i < k; i++) {
        int a, b, score_a, score_b; cin >> a >> b >> score_a >> score_b;
        a--; b--;

        if (score_a > score_b)
            adj[b].push_back(a);
        else
            adj[a].push_back(b);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        visited = vector<bool>(n, false);
        if (in_cycle(i, {}))
            ans++;
    }

    cout << ans;
}
*/