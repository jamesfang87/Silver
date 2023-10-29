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

    int gcd[n + 1]; gcd[0] = 0;
    int reverse_gcd[n + 1]; reverse_gcd[0] = 0;
    for (int i = 0; i < n; i++) {
        gcd[i + 1] = __gcd(gcd[i], numbers[i]);
        reverse_gcd[i + 1] = __gcd(reverse_gcd[i], reversed_numbers[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int reversed = n - i;
        ans = max(ans, __gcd(reverse_gcd[reversed - 1], gcd[i]));
    }
    cout << ans;
}