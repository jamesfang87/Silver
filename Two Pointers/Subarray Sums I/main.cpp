#include <iostream>

using namespace std;

int main() {
    int n, target; cin >> n >> target;

    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int l_ptr = 0, r_ptr = 0, sum = 0, ans = 0;
    while (l_ptr < n) {
        while (r_ptr < n && sum < target) {
            sum += nums[r_ptr]; r_ptr++;
        }

        if (sum == target) {
            ans++;
        }

        sum -= nums[l_ptr]; l_ptr++;
    }

    cout << ans;
}
