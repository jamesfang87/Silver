#include <iostream>
#include <vector>
using namespace std;

vector<int> num_subordinates;
vector<vector<int> > adj;

void dfs(int person, int prev_person) {
    num_subordinates[person] = 0;
    for (int subordinate : adj[person]) {
        if (subordinate != prev_person) {
            dfs(subordinate, person);
        }
        num_subordinates[person] += num_subordinates[subordinate] + 1;
    }
}

int main() {
    int n; cin >> n;
    adj = vector<vector<int> >(n + 1);
    for (int i = 2; i <= n; i++) {
        int boss; cin >> boss;
        adj[boss].push_back(i);
    }

    num_subordinates = vector<int>(n + 1);
    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        cout << num_subordinates[i] << ' ';
    }
}
