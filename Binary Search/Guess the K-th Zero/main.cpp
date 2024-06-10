#include <iostream>
using namespace std;

int num_zeros(int right, int left) {
    cout << "? " << left << " " << right << endl;
    int sum; cin >> sum;
    return right - left + 1 - sum;
}

int main() {
    /*
    in this problem, we are limited to 20 queries;
    with the potential size of the hidden array being very large, this forces us to use binary search
    we are also only alloted one query for each iteration of binary search
    since log2(200001) is about 17.6

    notice that we can easily figure out the number of zeros in an interval using math:
    suppose of query of ? L R returns an arbitary value, x,
    the number of zeros in the interval [L, R] = R - L + 1 - x
    now, let's define a function Z(x) which outputs the number of zeros from [1, x]

    with these defintions, it follows that the kth zero occurs at the first index which Z(x) returns k

    now, let's create a monotonic function which will allow us to use binary search:
    we can define another function F(x) = {0 if Z(x) < k
                                           1 if Z(x) >= k}

    with this defintion of F(x), we simply need to find the first value where F(x) is 1
    which we can do easily with binary search
    */
    int n, t, k; cin >> n >> t >> k;

    int low = 1, high = n + 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (num_zeros(mid, 1) >= k) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    cout << "! " << low;
}
