#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

void solve() {
    int n; cin >> n;

    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    // we have to choose the largest number in the array at each step
    // if we don't, then our next x will be less than the largest number in the array
    // and we won't able to delete that number

    // thus we want to brute force the second number we choose in the first step
    // after that, we update x and the choose the largest number
    // the second number we choose becomes trivial to find
    // it's just the one that satisfies x = max + b
    // if it's not present then our choice the second number for the first step doesn't work
    for (int i = 0; i < a.size() - 1; i++) {
        int first_x = a[a.size() - 1] + a[i];

        multiset<int> remaining;
        for (int j = 0; j < a.size() - 1; j++) {
            if (i == j)
                continue;

            remaining.insert(a[j]);
        }

        bool can_discard = true;
        vector<pair<int, int>> sol = {{a[a.size() - 1], a[i]}};
        int x = a[a.size() - 1];
        for (int j = 0; j < n - 1; j++) {
            int max = *remaining.rbegin();
            remaining.erase(prev(remaining.end()));

            auto pos = remaining.find(x - max);
            if (pos == remaining.end()) {
                can_discard = false;
                break;
            } else {
                remaining.erase(pos);
                sol.emplace_back(max, x - max);
            }
            x = max;
        }

        if (can_discard) {
            cout << "YES\n" << first_x << '\n';
            for (auto p : sol) {
                cout << p.first << ' ' << p.second << '\n';
            }
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    int t; cin >> t;

    while (t--) {
        solve();
    }
}