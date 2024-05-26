#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <cstdint>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> prices(n);
    for (auto& department : prices) {
        cin >> department.first >> department.second;
    }
    sort(prices.begin(), prices.end(), greater<>());

    multiset<int> b_prices = {static_cast<int>(-1e9), static_cast<int>(2e9)};
    for (int i = 0; i < n; i++) {
        b_prices.insert(prices[i].second);
    }

    int ans = INT32_MAX;
    int friend1;
    int friend2 = INT32_MIN;
    // the most expensive gift for one person will be bought at index i
    for (int i = 0; i < n; i++) {
        friend1 = prices[i].first;
        if (i != 0) {
            friend2 = max(friend2, prices[i - 1].second);
            ans = min(ans, abs(friend1 - friend2));
        }

        auto pos = b_prices.find(prices[i].second);
        if (pos != b_prices.end()) {
            b_prices.erase(pos);
        }

        auto it = b_prices.lower_bound(friend1);
        int right = *it, left = *prev(it);
        if (right > friend2) {
            ans = min(ans, abs(right - friend1));
        }
        if (left > friend2) {
            ans = min(ans, abs(left - friend1));
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
    }
}
