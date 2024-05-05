#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n; cin >> n;
    int lengths[n];
    for (int i = 0; i < n; i++) {
        cin >> lengths[i];
    }

    sort(lengths, lengths + n);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(lengths[i] - lengths[n / 2]);
    }
    cout << ans;
}
