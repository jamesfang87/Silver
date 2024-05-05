#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> undirected_graph;
vector<int> adj;
vector<bool> visited;

void dfs(int node) {
    for (int neighbor : undirected_graph[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            dfs(neighbor);
        }
    }
}

int cycle_length(int start) {
    int a = start; int b = start;
    do {
        a = adj[a];
        b = adj[adj[b]];
    } while (a != b);

    a = start;
    while (a != b) {
        a = adj[a];
        b = adj[b];
    }

    int length = 0;
    do {
        b = adj[b];
        length++;
    } while (a != b);

    return length;
}

int main() {
    ifstream fin("shuffle.in");
    ofstream fout("shuffle.out");

    int n; fin >> n;
    adj = vector<int>(n);
    undirected_graph = vector<vector<int>>(n);
    for (int i = 0; i < n; i++) {
        int to; fin >> to; to--;
        adj[i] = to;

        undirected_graph[i].push_back(to);
        undirected_graph[to].push_back(i);
    }

    visited = vector<bool>(n);
    vector<int> components;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            components.push_back(i);
        }
    }

    int ans = 0;
    for (int c : components) {
        ans += cycle_length(c);
    }

    fout << ans;
}
