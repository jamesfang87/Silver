#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    pair<int, int> nums[n];
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        nums[i] = {temp, i};
    }

    sort(nums, nums + n);
    for (int i = 0; i < n; i++) {
        int l = 0, r = n - 1;
        while (r != l) {
            int target = x - nums[i].first;
            if (l != i && r != i && nums[l].first + nums[r].first == target) {
                cout << nums[i].second + 1 << ' ' << nums[l].second + 1 << ' ' << nums[r].second + 1;
                return 0;
            }

            if (nums[l].first + nums[r].first < target) {
                l++;
            } else {
                r--;
            }
        }
    }
    cout << "IMPOSSIBLE";
}
