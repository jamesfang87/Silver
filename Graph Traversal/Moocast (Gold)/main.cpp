#include <fstream>
#include <vector>
using namespace std;

vector<bool> visited;

struct Cow {
    int x, y;
};

bool can_reach(Cow a, Cow b, int power) {
    int dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);

    return dist <= power;
}

void dfs(int cow, const vector<vector<int>>& adj) {
    for (int c : adj[cow]) {
        if (!visited[c]) {
            visited[c] = true;
            dfs(c, adj);
        }
    }
}

bool connected(int power, const vector<Cow>& cows) {
    vector<vector<int>> adj(cows.size());
    for (int i = 0; i < cows.size(); i++) {
        for (int j = i + 1; j < cows.size(); j++) {
            if (can_reach(cows[i], cows[j], power)) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    visited = vector<bool> (cows.size());
    dfs(0, adj);
    for (int i = 0; i < cows.size(); i++) {
        if (!visited[i]) return false;
    }
    return true;
}

int main() {
    ifstream in("moocast.in");
    ofstream out("moocast.out");

    int n; in >> n;
    vector<Cow> cows(n);
    for (Cow& c : cows)
        in >> c.x >> c.y;

    int l = 0, r = 1250000001;
    while (l < r) {
        // this our power
        int m = l + (r - l) / 2;

        if (connected(m, cows))
            r = m;
        else
            l = m + 1;
    }
    out << l;
}
