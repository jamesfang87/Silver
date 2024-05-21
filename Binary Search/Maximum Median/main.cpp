#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long num_operations(vector<int>& array, int target_median) {
    long long ret = 0;
    for (int i = array.size() / 2; i < array.size(); i++) {
        ret += max(0, target_median - array[i]);
    }
    return ret;
}

int main() {
    int n, k; cin >> n >> k;
    vector<int> array(n);
    for (int& a : array) {
        cin >> a;
    }
    sort(array.begin(), array.end());

    // to increase the medium to a certain value, we must increase the current median and every value above
    // we can binary search on the possible target medians and see if the number of operations needed is above or below the allowed operations

    int low = 0, high = 2e9;
    while (low < high) {
        int mid = low + (high - low + 1) / 2;
        if (num_operations(array, mid) <= k) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    cout << low;
}
