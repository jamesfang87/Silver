#include <iostream>
#include <vector>
#include <stack>
using namespace std;


vector<vector<int>> adj;
vector<int> visit_order, low;
stack<int> s;
vector<int> SCC_heads;
int counter = 1;

void dfs(int city) {
    s.push(city);
    visit_order[city] = counter;
    low[city] = counter;
    counter++;

    for (int neighbor : adj[city]) {
        if (visit_order[neighbor] == -1)
            dfs(neighbor);

        if (visit_order[neighbor] >= 1) // condition for update
            low[city] = min(low[city], low[neighbor]);

    }

    if (low[city] == visit_order[city]) { // if this is a root (start) of an SCC
        SCC_heads.push_back(city);
        while (true) {
            int v = s.top(); s.pop(); visit_order[v] = 0;
            if (city == v) break;
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    adj = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
    }

    // we can run bfs/dfs on each city
    visit_order = vector<int>(n, -1);
    low = vector<int>(n, -1);
    for (int i = 0; i < n; i++) {
        if (visit_order[i] == -1)
            dfs(i);
    }


    if (SCC_heads.size() == 1)
        cout << "YES";
    else
        cout << "NO\n" << SCC_heads[0] + 1 << ' ' << SCC_heads[1] + 1;
}
