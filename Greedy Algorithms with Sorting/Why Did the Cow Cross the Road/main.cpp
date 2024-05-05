#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("helpcross.in");
    ofstream fout("helpcross.out");

    int c, n; fin >> c >> n;

    multiset<int> chickens;
    for (int i = 0; i < c; i++) {
        int temp = 0; fin >> temp;
        chickens.insert(temp);
    }

    pair<int, int> cows[n];
    for (auto& cow : cows) {
        fin >> cow.second >> cow.first;
    }
    sort(cows, cows + n);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto chicken = chickens.lower_bound(cows[i].second);
        if (chicken != chickens.end() && *chicken <= cows[i].first) {
            ans++;
            chickens.erase(chicken);
        }
    }
    fout << ans;
}