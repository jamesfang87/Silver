#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct wormhole {
    int a, b, width;
};

int main() {
    ifstream fin("wormsort.in");
    ofstream fout("wormsort.out");

    int n, m; fin >> n >> m;

    vector<int> original_pos(n); for (int& cow : original_pos) {
        fin >> cow;
        cow--;
    }

    vector<wormhole> wormholes(m);
    vector<vector<std::pair<int, int>>> adj(n);
    int max_width = -1;
    for (wormhole& w : wormholes) {
        fin >> w.a >> w.b >> w.width;
        w.a--; w.b--;

        adj[w.a].emplace_back(w.b, w.width);
        adj[w.b].emplace_back(w.a, w.width);

        max_width = max(max_width, w.width);
    }

    if (is_sorted(original_pos.begin(), original_pos.end())) {
        fout << -1;
        return 0;
    }

    int loww = 0, high = max_width + 1, ans;
    while (loww <= high) {
        int mid = (high + loww) / 2;

        vector<int> components(n, -1);
        int cur_component = 0;
        for (int c = 0; c < n; c++) {
            if (components[c] != -1) continue;
            
            stack<int> q; q.push(c);
            
            while (!q.empty()) {
                int cur = q.top(); q.pop();

                components[cur] = cur_component;
                for (const auto &[cow, w] : adj[cur]) {
                    if (components[cow] == -1 && w >= mid) {
                        q.push(cow);
                    }
                }
            }
            cur_component++;
        }

        bool sortable = true;
        for (int cow = 0; cow < n; cow++) {
            if (components[cow] != components[original_pos[cow]]) {
                sortable = false;
                break;
            }
        }

        if (sortable) {
            loww = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }

    }
    fout << ans;
}