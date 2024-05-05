#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct cow {
    int x, y;
};

struct component {
    int min_x, max_x;
    int min_y, max_y;
};

int main() {
    ifstream fin("fenceplan.in");
    ofstream fout("fenceplan.out");

    int n, m; fin >> n >> m;
    vector<cow> cows(n);
    for (cow& c : cows) {
        fin >> c.x >> c.y;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b; fin >> a >> b;
        a--; b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // find connected components
    vector<bool> visited(n, false);
    component cur = {INT32_MAX, INT32_MIN, INT32_MAX, INT32_MIN};

    int connected = 0;
    int ans = INT32_MAX;
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int current_cow = q.front();
            q.pop();


            visited[current_cow] = true;
            cur.min_x = min(cur.min_x, cows[current_cow].x);
            cur.max_x = max(cur.max_x, cows[current_cow].x);

            cur.min_y = min(cur.min_y, cows[current_cow].y);
            cur.max_y = max(cur.max_y, cows[current_cow].y);


            for (int neighbor : adj[current_cow]) {
                if (!visited[neighbor])
                    q.push(neighbor);
            }
        }

        ans = min(ans, 2 * abs(cur.max_x - cur.min_x) + 2 * abs(cur.max_y - cur.min_y));
        cur = {INT32_MAX, INT32_MIN, INT32_MAX, INT32_MIN};
    }

    fout << ans;
}
