#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> adj;
vector<vector<int>> components;
vector<int> component_of;

void dfs(int cur, int component) {
    if (component_of[cur] == -1) {
        component_of[cur] = component;

        for (int neighbor : adj[cur]) {
            dfs(neighbor, component);
        }
    }
}

long long find_min_cost(int c1, int c2) {
    long long ans = INT64_MAX;

    // the time complexity of this function is O(nlogm)
    // n = size of components[c1] and m = size of components[c2]
    // we want m > n since m is inside a log
    if (components[c2].size() < components[c1].size()) {
        // move the smaller number to the linear part
        // and the larger number to the log part
        swap(c1, c2);
    }

    for (int a: components[c1]) {
        auto it = lower_bound(components[c2].begin(), components[c2].end(), a);

        int upper = *it;
        if (it == components[c2].begin()) {
            ans = min(ans, (long long) (a - upper) * (a - upper));
            continue;
        }

        int lower = *(it - 1);
        if (it == components[c2].end()) {
            ans = min(ans, (long long) (a - lower) * (a - lower));
            continue;
        }

        long long closest = min((long long) (a - upper) * (a - upper),
                                (long long) (a - lower) * (a - lower));
        ans = min(ans, closest);
    }
    return ans;
}

long long solve() {
    int n, m;
    cin >> n >> m;

    adj = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int component_num = 0;
    component_of = vector<int>(n, -1);
    for (int i = 0; i < n; i++) {
        if (component_of[i] == -1) {
            dfs(i, component_num);
            component_num++;
        }
    }

    components = vector<vector<int>>(component_num);
    for (int i = 0; i < n; i++) {
        int c = component_of[i];
        components[c].push_back(i);
    }

    // options:
    // 1. trivial answer: if start and end are in the same component, return 0
    // 2. we can choose to build just one path. this can directly connect 1 and n or their components
    // 3. we can choose one component to connect two paths to: one path to the start, one path to the end

    // option 1:
    if (component_of[0] == component_of[n - 1])
        return 0;

    // option 2:
    long long option2 = find_min_cost(component_of[0], component_of[n - 1]);
    if (components.size() == 2)
        return option2;

    // option 3:
    long long option3 = INT64_MAX;
    for (int c = 1; c < components.size(); c++) {
        if (c == component_of[n - 1])
            continue;

        long long path1 = find_min_cost(component_of[0], c);
        long long path2 = find_min_cost(c, component_of[n - 1]);
        option3 = min(option3, path1 + path2);
    }
    return min(option2, option3);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cout << solve() << endl;
    }
}