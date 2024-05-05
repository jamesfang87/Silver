#include <fstream>
#include <vector>
using namespace std;

struct Edge {
    int neighbor;
    char restriction;
};

vector<vector<Edge>> adj;
vector<int> color;

bool dfs(int cur) {
    int cur_color = color[cur];

    for (auto e : adj[cur]) {
        int correct_color;
        if (e.restriction == 'D')
            correct_color = !cur_color;
        else
            correct_color = cur_color;

        if (color[e.neighbor] != -1) {
            if (correct_color != color[e.neighbor]) {
                return false;
            }
        } else {
            color[e.neighbor] = correct_color;
            if (!dfs(e.neighbor)) {
                return false;
            }
        }
    }

    return true;
}
int main() {
    ifstream fin("revegetate.in");
    ofstream fout("revegetate.out");
    int n, m; fin >> n >> m;

    adj = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        char restriction; int a, b; fin >> restriction >> a >> b;
        a--; b--;

        adj[a].push_back({b, restriction});
        adj[b].push_back({a, restriction});
    }

    color = vector<int>(n, -1);

    string ans = "1";
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            if (!dfs(i)) {
                fout << "0";
                return 0;
            } else {
                ans += '0';
            }
        }
    }
    fout << ans;
}
