#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
    int k, m, n; cin >> k >> m >> n;

    vector<pair<int, int>> patches(k);
    for (auto& patch : patches) {
        cin >> patch.first >> patch.second;
    }
    sort(patches.begin(), patches.end());

    vector<int> farmer_nhoj(m + 2);
    farmer_nhoj[0] = -1e9; farmer_nhoj[m + 1] = 2e9;
    for (int i = 1; i <= m; i++) {
        cin >> farmer_nhoj[i];
    }
    sort(farmer_nhoj.begin(), farmer_nhoj.end());

    // farmer nhoj's cows divide the farm into M + 1 intervals
    // for the first and last interval, farmer john can claim them all with one cow
    // for the first, just place the cow slightly to the left of farmer nhoj's
    // similar strategy for the last, place the cow slightly to the right

    // for all other intervals, farmer john can claim all the patches inside with two cows
    // the reasoning is similar to the first and last:
    // given an interval (l, r), we can place cows slight to the right of l and vice versa for r
    // that way, all patches in the interval are closer to fj's cows

    // but fj doesn't always have enough cows, and we want to see how many patches he can claim with just one
    // for any location q within the interval (l, r), the interval is further split into 2 sub-intervals,
    // one to the left of q and one to the right.
    // fj can claim the half of the left sub-interval closer to q and same for the right sub-interval

    // length of the range in the left sub-interval that fj can claim:
    // (q - l) / 2
    // length of the range in the right sub-interval that fj can claim:
    // (r - q) / 2


    // thus the total range of the patches that fj can claim is:
    // (l + (q - l) / 2, q + (r - q) / 2) = (2l/2 + (q - l) / 2, 2q/2 + (r - q) / 2)
    //                                    = ((2l + q - l) / 2, (2q + r - q) / 2)
    //                                    = ((l + q) / 2, (q + r) / 2)
    // it follows that the length of this range is (r - l) / 2

    // we use 2P to find the max 1 cow tastiness for each interval
    // the sum of the tastiness of all patches in the interval is the 2 cow tastiness

    // finally, we can create a vector of all the max 1 cow tastiness for each interval
    // and add (two-cow tastiness - one-cow tastiness) to simulate putting another cow there

    // max amount of tastiness in each interval
    vector<long long> max_tastiness;
    int left, right = 0;
    for (int i = 0; i < m + 1; i++) {
        double len = (double) (farmer_nhoj[i + 1] - farmer_nhoj[i]) / 2;

        long long two_cow_tastiness = 0; // tastiness of all the patches in this interval (see above)
        long long one_cow_tastiness = 0; // max tastiness in this interval with one cow
        long long cur_tastiness = 0; // cur tastiness of the sliding window

        left = right;
        // while right is in range and we are still in the interval
        while (right < k && patches[right].first < farmer_nhoj[i + 1]) {
            // if we have not created the window of max length
            if (patches[right].first - patches[left].first < len) {
                // extend the window
                cur_tastiness += patches[right].second;
                two_cow_tastiness += patches[right].second;
                right++;
            } else {
                cur_tastiness -= patches[left].second;
                left++;
            }
            one_cow_tastiness = max(one_cow_tastiness, cur_tastiness);
        }

        max_tastiness.push_back(one_cow_tastiness);
        max_tastiness.push_back(two_cow_tastiness - one_cow_tastiness);
    }

    sort(max_tastiness.begin(), max_tastiness.end(), greater<>());
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += max_tastiness[i];
    }
    cout << ans;
}