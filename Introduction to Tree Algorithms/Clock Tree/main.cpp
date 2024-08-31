#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

int clocks[2500];
vector<int> adj[2500];

int group1 = 0, group2 = 0, group1_size = 0, group2_size = 0;

void dfs(int cur, int prev, bool color) {
    if (color) {
        group1 += clocks[cur];
        group1_size++;
    } else {
        group2 += clocks[cur];
        group2_size++;
    }
    
    for (int neighbor : adj[cur]) {
        if (neighbor != prev) {
            dfs(neighbor, cur, !color);
        }
    }
}

int main() {
    ifstream fin("clocktree.in");
    ofstream fout("clocktree.out");
    
    int n; fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> clocks[i];
    }
    
    for (int i = 1; i < n; i++) {
        int a, b; fin >> a >> b;
        a--; b--;
        
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // lets first examine the case where there are only 2 nodes in a tree
    // if readings on the clocks differ by 1, then we can start at the 
    // larger node, traveling back and forth between the 2 nodes
    // before they both reach 12.
    // however, if the readings of the clocks differ by more than 1, 
    // then it is impossible to make both clocks read 12.
    // 
    // since trees are bipartite, we can extend this observation to trees with n > 2
    // we can treat the first group of nodes as one singular node
    // and the second group as another node. The values (clock readings) of each of these
    // 'supernodes' is the sum of all clock readings of nodes in the group
    // We can easily see that the difference of the groups, which is necessary to check
    // if we can make all clocks equal to 12, can never change:
    // to get the difference to increase, we must travel to another node in the same group
    // however, because of the way that the tree is colored, we must go through
    // another node in the 2nd group meaning the difference is still the same
    
    dfs(0, -1, 0);
    
    group1 %= 12, group2 %= 12;
    if (group1 == group2) {
        fout << n;
    } else if (group1 - group2 == 1 || (group1 == 0 && group2 == 11)) {
        fout << group1_size;
    } else if (group2 - group1 == 1 || (group1 == 11 && group2 == 0)) {
        fout << group2_size;
    } else {
        fout << 0;
    }
}