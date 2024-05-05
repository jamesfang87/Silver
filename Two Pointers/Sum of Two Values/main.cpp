#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;
int main() {
    int n, x; cin >> n >> x;

    pair<int, int> nums[n];
    for (int i = 0; i < n; i++) {
        int temp; cin >> temp;
        nums[i] = {temp, i};
    }

    sort(nums, nums + n);

    int l_ptr = 0, r_ptr = n - 1;
    while (r_ptr > l_ptr) {
        if (nums[l_ptr].first + nums[r_ptr].first < x) {
            l_ptr++;
        } else if (nums[l_ptr].first + nums[r_ptr].first > x) {
            r_ptr--;
        } else {
            std::cout << nums[l_ptr].second + 1 << ' ' << nums[r_ptr].second + 1;
            return 0;
        }
    }
    cout << "IMPOSSIBLE";
}
