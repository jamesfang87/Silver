#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin>> n;

    long long mod[n], cur_sum = 0;
    fill(mod, mod + n, 0);
    for (int i = 0; i <= n; i++) {
        mod[(cur_sum % n + n) % n]++;
        int temp; cin >> temp;
        cur_sum += temp;
    }

    long long ans = 0;
    for (long long i : mod) {
        ans += i * (i - 1) / 2;
    }
    cout << ans;
}