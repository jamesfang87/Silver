#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long i64;

bool solve() {
    int n; cin >> n;
    i64 d[2 * n]; // array d described in problem statement
    unordered_map<i64, int> frequency;
    for (int i = 0; i < 2 * n; i++) {
        i64 val; cin >> val;
        
        d[i] = val;
        frequency[val]++;
    }
    
    // each value in d[i] can only appear twice- once for a[i] and once for -1 * a[i]
    // a is also comprised of distinct integers so val exists only once
    vector<i64> unique_d;
    for (auto& [val, freq] : frequency) {
        if (freq != 2 || val % 2 != 0) 
            return false;

        unique_d.push_back(val);
    }

    sort(unique_d.begin(), unique_d.end());
    // abs(a[n] - a[i]) + abs(a[n] + a[i]) = a[n] - a[i] + a[n] + a[i] = 2a[n]
    // d[n] = 2 * n * a[n] as 1 <= i <= n
    // a[n] = d[n] / 2n

    unordered_set<i64> a; 
    i64 last = 0;
    for (int i = n - 1; i >= 0; i--) {
        if ((unique_d[i] / 2 - last) % (i + 1) != 0) {
            return false;
        }

        i64 val = (unique_d[i] / 2 - last) / (i + 1);
        if (val <= 0) {
            return false;
        } else {
            a.insert(val), a.insert(-1 * val);
            last += val;
        }
    }

    // checks that we have 2 * n distinct integers
    // in the array that we generated
    return a.size() == 2 * n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while (t--) {
        if (solve()) cout << "YES\n";
        else cout << "NO\n";
    }
}