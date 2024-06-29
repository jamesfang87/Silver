#include <bits/stdc++.h>
using namespace std;

int n; 
vector<int> positions, velocities;

bool possible(double time) {
    double left = 0, right = 1e9;
    for (int i = 0; i < n; i++) {
        double low_bound = positions[i] - velocities[i] * time;
        double high_bound = positions[i] + velocities[i] * time;

        if (low_bound > right || high_bound < left) {
            return false;
        } else {
            left = max(low_bound, left);
            right = min(high_bound, right);
        }
    }
    return true;
}

int main() {
    cin >> n;
    positions.resize(n); velocities.resize(n);
    
    for (int& pos : positions) {
        cin >> pos;
    }

    for (int& v : velocities) {
        cin >> v;
    }

    double low = 0, high = 1e9;
    while (high - low > 1e-7) {
        double mid = low + (high - low) / 2;
        if (possible(mid)) {
            high = mid;
        } else {
            low = mid + 1e-6;
        }
    }
    cout.precision(12); cout << low;
}