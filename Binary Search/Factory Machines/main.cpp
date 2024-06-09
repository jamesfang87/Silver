#include <cmath>
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, t;

bool valid(unsigned long long t_max, const vector<int>& efficiencies) {
    unsigned long long remaining_tasks = t;
    for (int efficiency : efficiencies) {
        /*
        one thing we have to take care of is overflow: since the max time can be 10^9 * 10^9 = 10^18,
        we must use unsigned long longs, which will also overflow when we subtract a number larger than it
        thus, end this loop when we overflow this way
        it also follows that once we produce more than the remaining tasks, we can return true
        */
        if (t_max / efficiency > remaining_tasks) {
            return true;
        } else {
            remaining_tasks -= t_max / efficiency;
        }
    }
    return remaining_tasks <= 0;
}

int main() {
    cin >> n >> t;
    vector<int> efficiencies(n);
    for (int& e : efficiencies) {
        cin >> e;
    }
    /*
    suppose that we have a maximum time, t, which we can not exceed
    we can delegate tasks to each machine, just enough to not exceed t
    then, we can binary search to find the least value of t such we can finish all tasks
    */
    unsigned long long low = 0, high = 1e19 + 1;
    while (low < high) {
        unsigned long long mid = low + (high - low) / 2;
        if (valid(mid, efficiencies)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    cout << low;
}
