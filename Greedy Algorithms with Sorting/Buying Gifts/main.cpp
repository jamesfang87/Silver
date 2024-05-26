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
    
    /*
     * sort by either gift prices for friend 1 or friend 2 in decreasing order. this code sorts for friend 1
     * 
     * the most expensive gift for friend 1 will be bought at index i (m1)
     * because the prices are sorted in decreasing order, we buy for friend 2 for all indices before i
     * since if we bought a gift for friend 1 in department j, where j < i, 
     * then we would lose the guarantee that the most expensive gift for friend 1 will be bought at index i
     * 
     * in order words, we fix m1, the price of the most expensive gift for friend 1.
     * 
     * to find m2, the price of the most expensive gift for friend 2, we take two steps per m1
     * firstly, we look at the prices for friend 2 before index i and update our ans
     * this can be done easily be keep a variable for m2 and updating per each iteration
     * 
     * secondly, we look at the prices after index i
     * we can initialize a multiset which contains all the prices of gifts we can purchase for f2
     * every iteration, we remove price for friend 2's gift at department i (as noted by the problem)
     * and find the two values closest to m1
     * note that because of the problem (m2 is the MAX price of a gift we buy for friend 2)
     * we must check that these values are above the current m2 before updating our answer
     */

    int ans = INT32_MAX;
    int friend1; // m1
    int friend2 = INT32_MIN; // m2
    // the most expensive gift for one person will be bought at index i
    for (int i = 0; i < n; i++) {
        friend1 = prices[i].first;
        
        // look at prices before index i
        if (i != 0) {
            friend2 = max(friend2, prices[i - 1].second);
            ans = min(ans, abs(friend1 - friend2));
        }
        
        // erase price for friend 2 at department i
        auto pos = b_prices.find(prices[i].second);
        if (pos != b_prices.end()) {
            b_prices.erase(pos);
        }
        
        // find values closest to m1
        auto it = b_prices.lower_bound(friend1);
        int right = *it, left = *prev(it);
        
        // which are above m2
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
