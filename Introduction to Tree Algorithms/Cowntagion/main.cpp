#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int> > adj;

int dfs(int src, int prev) {
    int num_infected = 1;
    int days_added = 0;
    
    // one neighbor, the prev farm that we came from, will already by infected
    // so we don't need to send a cow to that farm,
    // thus we check if num_infected is less than num neighbors - 1 + 1 (for the farm itself)
    // this holds for everything except farm 1, since we do not come from anywhere
    while (num_infected < adj[src].size() + (src == 0)) {
        days_added++;
        num_infected *= 2;
    }
    
    for (auto neighbor : adj[src]) {
        if (neighbor != prev) {
            days_added += dfs(neighbor, src) + 1;
        }
    }
    
    return days_added;
}

int main() {
    cin >> n;
    
    adj = vector<vector<int> >(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    /*
    subtask 1: it is optimal to increase the amount of sick cows until greater than n 
               and then move one cow to each of the neighbors of farm 1
    
    subtask 2: in this subtask, the graph is arranged so that some "arms" of farms extend
               out from farm 1. it is optimal to increase the amount of sick cows in farm 1
               so that it is at least the number of "arms". then, move one cow to the first 
               farm in each arm. then, slowly begin to propagate forward in each arm, doubling
               the amount of cows in each farm on the "edge" (1 -> 2) and moving the extra cow the 
               neighboring uninfected farm.
               
    full solution: we can essentially "combine" observations from these 2 subtasks into a general algorithm
    when at a farm:
    1. double the amount of infected cows at a farm until it is greater than the number of uninfected neighbors
    2. move to each uninfected neighbor
    
    and update the amount of days accordingly
    
    there is a trick to figuring out quickly the number of uninfected neighbors
    since the graph of farms is a tree, every other neighbor except the prev farm we came from
    will be uninfected giving us adj[src].size() as the number of uninfected neighbors
    this is true as there is only one path from one node to another in a tree. thus, if we visit a node,
    there is no way we have visited it before, as we will be on the singular path to the farm.
    
    note that this holds for every farm except farm 1, which will have adj[src].size() + 1 neighbors
    since we start at farm 1, ie there is no previous farm that we visit before arriving at farm 1
    */
    
    cout << dfs(0, -1);
}
