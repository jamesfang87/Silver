#include <iostream>
#include <map>
using namespace std;

long long solve() {
    int len; cin >> len;
    string nums; cin >> nums;

    int sums[len + 1]; sums[0] = 0;
    for (int i = 0; i < len; i++) {
        sums[i + 1] = sums[i] + (nums[i] - '0');
    }

    map<int, long long> appearances;

    for (int i = 0; i <= len; i++) {
        appearances[sums[i] - i]++;
    }

    long long ans = 0;

    for (auto appearance : appearances) {
        ans += appearance.second * (appearance.second - 1) / 2;
    }

    return ans;

}

int main() {
    int test_cases; cin >> test_cases;
    while (test_cases--) {
        cout << solve() << endl;
    }
}