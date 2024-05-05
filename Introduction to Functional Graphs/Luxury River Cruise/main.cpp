#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> adj;

int next(int node, char dir) {
    if (dir == 'L') {
        return adj[node][0];
    } else {
        return adj[node][1];
    }
}

int main() {
    ifstream fin("cruise.in");
    ofstream fout("cruise.out");

    int n, m, k;
    fin >> n >> m >> k;
    adj = vector<vector<int>>(n);
    for (int i = 0; i < n; i++) {
        int left, right; fin >> left >> right;
        left--; right--;
        adj[i].push_back(left);
        adj[i].push_back(right);
    }

    vector<char> directions(m);
    for (int i = 0; i < m; i++) {
        fin >> directions[i];
    }

    vector<int> end_locations(n);
    for (int i = 0; i < n; i++) {
        end_locations[i] = i;

        for (char dir : directions) {
            end_locations[i] = next(end_locations[i], dir);
        }
    }

    int tortoise = 0, hare = 0;

    do {
        tortoise = end_locations[tortoise];
        hare = end_locations[end_locations[hare]];
    } while (tortoise != hare);

    tortoise = 0;
    vector<int> path;

    while (tortoise != hare) {
        path.push_back(tortoise);
        tortoise = end_locations[tortoise];
        hare = end_locations[hare];
    }

    if (path.size() > k) {
        fout << path[k] + 1;
        return 0;
    }

    k -= path.size();

    vector<int> cycle;

    do {
        cycle.push_back(tortoise);
        tortoise = end_locations[tortoise];
    } while (tortoise != hare);

    k %= cycle.size();
    fout << cycle[k] + 1;
}
