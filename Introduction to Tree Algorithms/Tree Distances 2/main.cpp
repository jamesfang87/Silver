#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int n;
int subtree_size[200000];
long long ans[200000];
vector<int> adj[200000];

// calculates the answer for node 1 and the subtree size for each node
void dfs1(int node, int prev, int degree) {
    subtree_size[node] = 1;
    ans[0] += degree;
    for (int subordinate : adj[node]) {
        if (subordinate != prev) {
            dfs1(subordinate, node, degree + 1);
            subtree_size[node] += subtree_size[subordinate];
        }
    }
}

void dfs2(int node, int prev) {
    // calculate using prev for all nodes except node 1, which 
    // which already its answer calcuated 
    if (node != 0) {
        ans[node] = ans[prev] - subtree_size[node] + (n - subtree_size[node]); 
    }    

    for (int neighbor : adj[node]) {
        if (neighbor != prev) {
            dfs2(neighbor, node);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // we can easily determine the sum of distances from
    // only one node to all other nodes in O(n) time
    // however, doing this for all nodes would take O(n^2) time
    // which is far too slow with n <= 2 * 10^5

    // let's first root the tree at node 1
    // then the distance to each node is simply its degree
    // then, let's consider how these distances change for 
    // the neighbors of node 1
    
    // for each of node 1 children of degree 1, 
    // if we reroot the tree so that it is the root,
    // we can see that those in that child's subtree have their
    // degree decreased by 1, while all other nodes outside 
    // that subtree have their degree increased by one

    // this is very useful, since we essentially have a 
    // constant time solution for each neighbor of a node!
    // if s is the sum for an ancestor, then the sum for a 
    // neighbor i is s - subtree_size[i] + n - subtree_size[i]

    // for our solution, we can run a dfs to calculate the 
    // ans for node 1 and label the subtree size for each node
    // then, we run another dfs, using our formula to calculate the answer
    
    dfs1(0, -1, 0); // calc subtree size and ans for node 1
    dfs2(0, -1); // use answer for node 1 to calculate ans for others

    for (int i = 0; i < n; i++) {
        printf("%lld ", ans[i]);
    }
}
