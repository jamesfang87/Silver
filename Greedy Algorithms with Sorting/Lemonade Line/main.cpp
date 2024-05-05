#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("lemonade.in");
    ofstream fout("lemonade.out");
    int n; fin >> n;
    int cows[n];
    for (int& c : cows) fin >> c;

    sort(cows, cows + n, greater<>());

    int ans = 0, len = 0;
    for (int& c : cows) {
        if (len <= c) {
            ans++;
            len++;
        }
    }
    fout << ans;
}
