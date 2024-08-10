#include <iostream>
using namespace std;


int main() {
    int n, q; cin >> n >> q;

    long long sequence[n];

    long long prefix_sum[n + 1]; prefix_sum[0] = 0;
    for (int i = 0; i < n; i++) {
        cin >> sequence[i];
        prefix_sum[i + 1] = prefix_sum[i] + sequence[i];
    }

    for (int i = 0; i < q; i++) {
        int lower, upper; cin >> lower >> upper;

        cout << prefix_sum[upper] - prefix_sum[lower] << '\n';
    }
}