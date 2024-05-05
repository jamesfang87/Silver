#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;


int main() {
    int n, k; cin >> n >> k;

    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; i++) {
        cin >> movies[i].second >> movies[i].first;
    }

    sort(movies.begin(), movies.end());

    multiset<int> end_times; for (int i = 0; i < k; i++) end_times.insert(-1);
    int ans = 0;
    for (auto m : movies) {
        if (m.second >= *end_times.begin()) {
            auto it = end_times.upper_bound(m.second);
            end_times.erase(--it);
            end_times.insert(m.first);
            ans++;
        }
    }
    cout << ans;
}