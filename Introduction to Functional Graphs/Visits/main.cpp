#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> undirected_graph;
vector<bool> visited;
vector<int> adj, moos;


void dfs(int cow) {
    visited[cow] = true;
    for (int neighbor : undirected_graph[cow]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}

int min_moos_in_cycle(int start) {
    int tortoise = start, hare = start;
    do {
        tortoise = adj[tortoise];
        hare = adj[adj[hare]];
    } while (tortoise != hare);

    int ret = INT32_MAX;
    do {
        ret = min(ret, moos[tortoise]);
        tortoise = adj[tortoise];
    } while (tortoise != hare);

    return ret;
}

int main() {
    /*
     * idea: it would take too long to loop through all permutations and simulate for each one
     * thus, we can use a kind of greedy solution
     *
     * the graph in the problem is a functional graph,
     * it will only have one cycle in each component at most
     *
     * in each component, there will be some paths leading up to a cycle:
     * 1 -> cycle <- 2
     *
     * if we process in the right order,
     * every cow in paths leading up to a cycle can moo
     * thus, we should process the paths first
     *
     * however, not all cows can moo if they are in a cycle
     * one will always not be able to:
     * 1 -> 2 -> 3 -> 1
     * if we start with 1, 2, or 3, one will not be able to moo:
     * start with 1: 1 moos, 2 moos, but 3 can't because 1 already left
     * start with 2: 2 moos, 3 moos, but 1 can't because 2 already left
     * start with 3: 3 moos, 1 moos, but 2 can't because 3 already left
     *
     * thus, since one can't moo in a cycle no matter what, we can add all v to our answer
     * and then subtract the least v to "simulate" one cow not mooing
     *
     * then we mark all cows in a component as complete
     *
     * thus for a component:
     * add up all v for cows in the component (can do when taking in)
     * keep v for all paths
     * keep v for cycle
     * minus the least v of a cow in the cycle
     */

    int n; cin >> n;
    adj = vector<int>(n); // the cow that cow i visits
    moos = vector<int>(n); // the amount of moos that are moo-ed when cow i visits cow adj[i]
    undirected_graph = vector<vector<int>>(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> adj[i] >> moos[i]; adj[i]--;
        ans += moos[i]; // fill ans with all v

        undirected_graph[i].push_back(adj[i]);
        undirected_graph[adj[i]].push_back(i);
    }

    visited = vector<bool>(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            ans -= min_moos_in_cycle(i);
            dfs(i); // mark as visited
        }
    }

    cout << ans;
}
