#include <iostream>
using namespace std;

int n, k;
int a[200000]; // array

bool possible_median(int num) {
    // count the number of values at least and less than num
    // if the number of values at least num is more than the amount less than num
    // then there exists a median that is at least num
    // 
    // for an implementation, we can replace all values less than num with -1 and 
    // all others (ones at least num) with 1
    // in the array, we can figure out if there is a subarray with positive sum
    // with a length that is at least k
    // this can be done with prefix sums
    
    int prefix_sums[200001] = {0};
    for (int i = 1; i <= n; i++) {
        int temp = -2 * (a[i - 1] < num) + 1;
        /*
        the equivalent of:
        if (a[i - 1] < num) {
            int temp = -1;
        } else {
            int temp = 1;
        }
        */
        prefix_sums[i] = temp + prefix_sums[i - 1];
    }
    
    int min_prefix = prefix_sums[0];
    int max_sum = prefix_sums[k];
    for (int i = k; i <= n; i++) {
        min_prefix = min(min_prefix, prefix_sums[i - k]);
        max_sum = max(max_sum, prefix_sums[i] - min_prefix);
    }
    
    return max_sum > 0;
}

int main() {
    cin >> n >> k; // length of array, length of subarray
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // binary search over the maximum median that we can achieve
    int l = -1, r = n;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (possible_median(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << l;
}