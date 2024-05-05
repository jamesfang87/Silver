#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    pair<int, int> tasks[n];
    for (auto &t : tasks) {
        cin >> t.first >> t.second;
    }

    sort(tasks, tasks + n);
    long long ans = 0, cur_time = 0;
    for (int i = 0; i < n; i++) {
        cur_time += tasks[i].first;
        ans += tasks[i].second - cur_time;
    }
    cout << ans;
}
