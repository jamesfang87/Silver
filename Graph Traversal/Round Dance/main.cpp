#include <set>
#include <vector>
#include <iostream>
using namespace std;

vector<set<int>> adj;
vector<bool> visited;
vector<int> component_of;

void dfs(int cur, int component) {
    visited[cur] = true;
    component_of[cur] = component;
    for (int neighbor : adj[cur]) {
        if (!visited[neighbor]) {
            dfs(neighbor, component);
        }
    }
}

bool can_merge(const vector<int>& component) {
    if (component.size() <= 2)
        return true;

    for (int neighbor : component) {
        if (adj[neighbor].size() == 1) {
            return true;
        }
    }
    return false;
}

void solve() {
    int n; cin >> n;

    adj = vector<set<int>>(n);
    for (int i = 0; i < n; i++) {
        int temp; cin >> temp; temp--;
        adj[i].insert(temp);
        adj[temp].insert(i);
    }

    visited = vector<bool>(n, false);
    int max_dances = 0;
    component_of = vector<int>(n, -1);
    for (int i = 0; i < n; i++) {
        if (visited[i])
            continue;

        max_dances++;
        dfs(i, max_dances - 1);
    }


    // first case, all of them are connected, no need to do any more work
    if (max_dances == 1) {
        cout << 1 << ' ' << 1 << '\n';
        return;
    }

    // second case, we need to merge some of the connected components
    // if number of edges = size of component then we can not merge
    // if number of edges = size - 1 then we can merge
    // if the size of the component is 2 then we can always merge

    vector<vector<int>> components(max_dances);
    for (int i = 0; i < component_of.size(); i++) {
        components[component_of[i]].push_back(i);
    }

    int num_mergeable = 0;
    for (const auto& component : components) {
        num_mergeable += can_merge(component);
    }

    int min_dances = (max_dances - max(1, num_mergeable) + 1);

    cout << min_dances << ' ' << max_dances << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
