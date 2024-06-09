#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int n, k;

bool valid(long long max_sum, vector<int> array) {
    long long cur_sum = 0;
    int subarrays_left = k;
    auto it = array.begin();
    while (it < array.end()) {
        if (*it > max_sum) {
            return false;
        }

        while (cur_sum + *it <= max_sum && it < array.end()) {
            cur_sum += *it;
            it++;
        }

        subarrays_left--;
        cur_sum = 0;
    }
    return subarrays_left >= 0;
}

int main() {
    cin >> n >> k;
    vector<int> array(n);
    for (int& a : array) {
        cin >> a;
    }

    long long low = 0, high = 2 * 10e5 * 10e9;
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (valid(mid, array)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    cout << low;
}
