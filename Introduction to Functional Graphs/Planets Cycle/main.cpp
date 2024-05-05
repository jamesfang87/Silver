#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<bool> visited;
vector<int> adj;
queue<int> path;
vector<int> ans;
int steps = 0;

void dfs(int planet) {
    path.push(planet);

    if (visited[planet]) {
        steps += ans[planet];
        return;
    }

    visited[planet] = true;
    steps++;
    dfs(adj[planet]);
}

int main() {
    int n; cin >> n;
    adj = vector<int>(n);
    for (int& a : adj) {
        cin >> a; a--;
    }

    /*
     * travel through a connected component using dfs() according to rules
     * inside dfs, keep track of how many planets we visited
     * when we hit a planet that we already visited, we add the number of planets
     * that it will visit to our counter
     *
     * if repeat was visited twice, we know that all planets after the first occurrence of repeat
     * is a cycle that we have not yet accounted for.
     * thus, it is fine when we add 0 to steps in dfs
     *
     * if repeat occurs only once and at the end, then we know that it leads to a cycle
     * that we have already accounted for
     * thus, we have saved time by already adding the amount of planets in the cycle
     *
     * after this, path contains all planets in our cycle.
     * we can remove them from path one by one and set the ans for that planet to step
     * since ans[adj[start]] == ans[start] - 1,
     * we subtract one from step
     *
     * there is an exception:
     * when we see the existence of a cycle, we stop decrementing step
     * this is because step is now the length of the cycle
     * and all planets in a cycle will have their ans equal the length of the cycle
     *
     * i'm pretty sure this only happens for a new cycle
     * like when repeat exists twice in the queue
     */
    
    ans = vector<int>(n, 0);
    visited = vector<bool>(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            steps = 0;
            dfs(i);
            int decrement = 1;

            while (!path.empty()) {
                if (path.front() == path.back()) {
                    decrement = 0;
                }

                ans[path.front()] = steps;
                steps -= decrement;
                path.pop();
            }
        }
    }

    for (int a : ans) {
        cout << a << ' ';
    }
}