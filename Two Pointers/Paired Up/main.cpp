#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
    ifstream in("pairup.in");
    ofstream out("pairup.out");
    int n; in >> n;

    vector<pair<int, int>> times;
    for (int i = 0; i < n; i++) {
        int temp, t; in >> temp >> t;
        times.push_back({t, temp});
    }

    // want to minimize the maximum time of pairings
    sort(times.begin(), times.end());

    int l = 0, r = n - 1, ans = 0;
    while (l < r) {
        int max_pairs = std::min(times[l].second, times[r].second);
        ans = std::max(ans, times[l].first + times[r].first);
        times[l].second -= max_pairs;
        times[r].second -= max_pairs;

        if (times[l].second == 0)
            l++;
        if (times[r].second == 0)
            r--;
    }

    out << ans;
}
