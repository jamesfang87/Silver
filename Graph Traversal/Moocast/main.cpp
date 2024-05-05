#include <vector>
#include <queue>
#include <fstream>
using namespace std;

struct cow {
    int x, y, power;
};

int bfs(int n, int start, const vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    int num_visited = 0;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int current_node = q.front();
        q.pop();

        if (!visited.at(current_node)) {
            visited.at(current_node) = true;
            num_visited++;
        }


        for (int neighbor : adj.at(current_node)) {
            if (!visited.at(neighbor))
                q.push(neighbor);
        }
    }

    return num_visited;
}

pair<bool, bool> can_reach(cow a, cow b) {
    int dist = ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));

    pair<bool, bool> result = {a.power * a.power >= dist,
                               b.power * b.power >= dist};

    return result;
}

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");
    int n; fin >> n;
    vector<cow> cows(n);
    for (cow& c : cows)
        fin >> c.x >> c.y >> c.power;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pair<int, int> results = can_reach(cows.at(i), cows.at(j));

            if (results.first)
                adj.at(i).push_back(j);

            if (results.second)
                adj.at(j).push_back(i);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(bfs(n, i, adj), ans);
    }
    fout << ans;
}
