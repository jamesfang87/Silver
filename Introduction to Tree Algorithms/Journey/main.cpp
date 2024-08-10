#include <iostream>
#include <vector>
using namespace std;
 
vector<vector<int>> adj;
double ans = 0.0;
 
void dfs(int src, int prev, int depth, double prob) {
    if (adj[src].size() == 1) {
        ans += depth * prob;
        return;
    }
    
    // the number of cities that the horse will go to is the number of 
    // paths leading out of the current city - 1 since 
    // there is a bidirectional path bewteen prev and src
    // this is not true for city 1 since there is no "prev" and we can 
    // travel to any of its neighbors
    // this is accounted for by the adj[0].push_back(0); on line 38
    double next_prob = prob / (adj[src].size() - 1);
    for (int neighbor : adj[src]) {
        if (neighbor == prev) {
            continue;
        }
 
        dfs(neighbor, src, depth + 1, next_prob);
    }
}
 
int main() {
    int n; cin >> n;
    adj = vector<vector<int>>(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    adj[0].push_back(0);

    /*
    root the tree at the starting city: city 1
    run a dfs keeping track of the depth and the probability, which is simple to calculate
    when there are no candidate cities (adj[src].size() == 1 as there is only the path that we came from)
    then add probability * depth to our ans
    */
 
    dfs(0, 0, 0, 1.0);
    printf("%.10f", ans); // be sure to use printf or std::setprecision as std::cout rounds
}