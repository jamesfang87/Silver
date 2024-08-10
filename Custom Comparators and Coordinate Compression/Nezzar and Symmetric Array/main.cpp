#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

bool solve() {
    int n; cin >> n;

    int d[2 * n]; // array d described in problem statement
    unordered_map<int, int> frequency;
    for (int i = 0; i < 2 * n; i++) {
        int val; cin >> val;
        
        d[i] = val;
        frequency[val]++;
    }
    
    // each value in d[i] can only appear twice- once for a[i] and once for -1 * a[i]
    // a is also comprised of distinct integers so val exists only once
    vector<int> unique_d;
    for (auto& [val, freq] : frequency) {
        if (freq != 2 || val % 2 != 0) 
            return false;

        unique_d.push_back(val);
    }

    sort(unique_d.begin(), unique_d.end());
    // abs(a[n] - a[i]) + abs(a[n] + a[i]) = a[n] - a[i] + a[n] + a[i] = 2a[n]
    // d[n] = 2 * n * a[n] as 1 <= i <= n
    // a[n] = d[n] / 2n

    // a[i - 1] = (d[i * 2 - 2] - 2 * a[i]) / (2n - 2)


    if (unique_d[n - 1] % (2 * n) != 0)
        return false;
    
    int last = unique_d[n - 1] / (2 * n);
    unordered_set<int> a = {last, -1 * last}; 

    for (int i = n - 2; i >= 0; i--) {
        if ((unique_d[i] - 2 * last) % (2 * i)) {

        }
    }





    for (int i = n; i > 0; i--) {
        if ((d[i * 2 - 1] - 2 * last) % (2 * n) != 0)
            return false;

        int val = (d[i * 2 - 2] - 2 * last) / (2 * n - 2);
        if (val <= 0) 
            return false;
        
        a.insert(val), a.insert(-1 * val);
    }

    for (int asdf : a) {
        cout << asdf << ' ';
    }
    cout << '\n';

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