#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;

    int numbers[n];
    for (int& i : numbers) {
        cin >> i;
    }

    int reversed_numbers[n];
    for (int i = 0; i < n; i++) {
        reversed_numbers[i] = numbers[n - 1 - i];
    }

    int forward_gcd[n + 1]; gcd[0] = 0;
    int reversed_gcd[n + 1]; reversed_gcd[0] = 0;
    for (int i = 0; i < n; i++) {
        forward_gcd[i + 1] = __gcd(forward_gcd[i], numbers[i]);
        reversed_gcd[i + 1] = __gcd(reversed_gcd[i], reversed_numbers[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int reversed = n - i;
        ans = max(ans, __gcd(reverse_gcd[reversed - 1], forwawrd_gcd[i]));
    }
    cout << ans;
}
