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
        reversed_numbers[i] = numbers[n - i - 1];
    }

    int prefixed_gcd[n + 1]; gcd[0] = 0;
    int suffixed_gcd[n + 1]; reversed_gcd[0] = 0;
    for (int i = 0; i < n; i++) {
        forward_gcd[i + 1] = __gcd(prefixed_gcd[i], numbers[i]);
        reversed_gcd[i + 1] = __gcd(suffixed_gcd[i], reversed_numbers[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, __gcd(suffixed_gcd[n - i - 1], prefixed_gcd[i]));
    }
    cout << ans;
}
