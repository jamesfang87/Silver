#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;

    long long nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    long long ans = 0, cur_sum = 0;
    map<long long, int> seen; seen[0] = 1;
    for (int i = 0; i < n; i++) {
        cur_sum += nums[i];
        ans += seen[cur_sum - target];
        seen[cur_sum]++;
    }


    cout << ans;
}