#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long n, k; 
vector<long long> nums;

// binary search to find number of occurrences of min
// implementation finds the first element that does not equal the minimum
long long get_occurrences_of_min(long long low, long long high, long long minimum) {
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (nums[mid] != minimum) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

// binary search to find number of occurrences of max
// implementation finds the first element that equals the maximum
long long get_occurrences_of_max(long long low, long long high, long long maximum) {
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (nums[mid] == maximum) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return n - low;
}

int main() {
    // intuitively, we should binary search on the difference
    // if our difference is too big, 
    // we can't reach such difference in under k moves
    cin >> n >> k;

    nums.resize(n);
    for (long long& a : nums) {
        cin >> a;
    }
    sort(nums.begin(), nums.end());

    // Suppose our array is 1 1 4 5 and k = 1
    // how can we decrease the difference by as much as possible (1)?
    // we can see that decreasing the max and increasing min allows for this

    // on the left side, we need to increase both 1's to decrease the difference
    // on the right side, we only need to decrease the 5

    // we can also see it's more "expensive" to increase the min in this case
    // as there are more occurrences of the minimum element

    // thus, it is better to be greedy in the side we choose to increase/decrease
    // while we still have operations left, 
    // we choose the best side to increase/decrease
    
    // greedy 2P except with binary search to skip past values

    long long operations_left = k;
    long long cur_min = nums[0], cur_max = nums[n - 1];
    long long l_ptr = 0, r_ptr = n; // exclusive right ptr
    while (l_ptr < r_ptr && operations_left > 0) {
        long long occurrences_of_min = get_occurrences_of_min(l_ptr, r_ptr, cur_min);
        long long occurrences_of_max = get_occurrences_of_max(l_ptr, r_ptr, cur_max);

        if (cur_min == cur_max) {
            std::cout << "0\n";
            return 0;
        }

        if (occurrences_of_max > operations_left && occurrences_of_min > operations_left) {
            std::cout << cur_max - cur_min << '\n';
            return 0;
        }

        if (occurrences_of_min < occurrences_of_max) {
            // find the value of the second smallest element
            long long index = occurrences_of_min; // index of second smallest
            long long second_smallest = nums[index];

            // figure out how much we can increase by:
            // we either increase by second_smallest - cur_min
            // or as much as we can by increasing all of them evenly
            long long can_increase_by = min(second_smallest - cur_min, operations_left / occurrences_of_min);
            operations_left -= occurrences_of_min * can_increase_by; // update operations left

            // instead of explicitly decreasing with a for loop like this :
            /*
            for (long long i = 0; i < index; i++) {
                nums[i] += can_increase_by;
            }
            */
            // we can do it "implicityly" by pretending all values to the left of l_ptr = updated cur_min

            cur_min += can_increase_by; // update the cur_min
            l_ptr = index; // set bounds of binary search to index of second smallest for binary search next iteration
        } else {
            long long index = n - occurrences_of_max - 1; // index of second largest
            long long second_largest = nums[index];

            // figure out how much we can decrease by:
            // we either decrease by cur_max - second_largest
            // or as much as we can by decreasing all of them evenly
            long long can_decrease_by = min(cur_max - second_largest, operations_left / occurrences_of_max);
            operations_left -= occurrences_of_max * can_decrease_by; // update operations left

            cur_max -= can_decrease_by; // update cur_max
            r_ptr = index; // set bounds of binary search to index of second largest for binary search next iteration
        }

        // debug
        /*
        cout << "occurrences of min: " << occurrences_of_min << '\n';
        cout << "occurrences of max: " << occurrences_of_max << '\n';
        cout << "operations left: " << operations_left << '\n';
        cout << "cur minimum: " << cur_min << '\n';
        cout << "cur maximum: " << cur_max << '\n';
        cout << '\n' << '\n';
        */
    }
    std::cout << cur_max - cur_min;
}