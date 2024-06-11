#include <fstream>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

vector<vector<pair<int, int> > > adj;

int dfs(int cur_video, int prev_video, int k) {
    int count = 1;
    cout << cur_video << ' ';
    for (auto [next_video, relevance] : adj[cur_video]) {
        if (next_video != prev_video && relevance >= k) {
            count += dfs(next_video, cur_video, k);
        }
    }
    return count;
}

int main() {
    ifstream fin("mootube.in");
    ofstream fout("mootube.out");

    int n, q; fin >> n >> q;
    adj = vector<vector<pair<int, int> > >(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int p, q, relevance;
        fin >> p >> q >> relevance;
        adj[p].emplace_back(q, relevance);
        adj[q].emplace_back(p, relevance);
    }

    for (int i = 0; i < q; i++) {
        int test_k, start_vid;
        fin >> test_k >> start_vid;
        cout << "visits: ";
        fout << dfs(start_vid, -1, test_k) - 1 << '\n';
    }
}
