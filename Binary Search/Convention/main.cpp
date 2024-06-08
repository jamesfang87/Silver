#include <cinttypes>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, bus_capacity;

bool can_arrange(long long max_time_diff, const vector<int>& arrival_times) {
    int buses_left = m;
    // iterator to the first cow in the current bus
    auto first_in  = arrival_times.begin();
    while (buses_left > 0) {
        // iterator to the first cow in the next bus
        auto new_first_in = upper_bound(arrival_times.begin(),
                                        arrival_times.end(),
                                        *first_in + max_time_diff);
        // this bus departs
        buses_left--;
        if (new_first_in - first_in > bus_capacity) {
            // if run out of space on the bus to fit all the cows in
            first_in += bus_capacity;
        } else {
            first_in = new_first_in;
        }

        if (first_in >= arrival_times.end()) {
            return true;
        }
    }
    return (first_in >= arrival_times.end());
}

int main() {
    /*
    a greedy solution seems to be able to run in time. however, unlike a similar problem, Diamond Collector,
    it is not easy to decide which bus to put a cow into.

    let's try doing a search instead:

    suppose that we have a target time difference, t, between any cow's departure and arrival
    then, we can check whether it is possible to arrange buses to meet this target time difference

    to do this, we can start at the cow which arrives first and add cows to its bus until:
    1. we run out of space on the bus
    2. the difference in arrival times exceeds t

    in both cases, we must put the next cow in a new bus

    if it is possible to optimally arrange buses, then we can put every cow in a bus without running out
    if not, we will run out of buses

    however, the times of the cows' arrival times span a large range: up to 10^9
    other than the fact that this range is clearly too large for a linear scan,
    let's look at the solution space to see what we can take advantage of:
    1. we notice that at some time difference, c, it is suddenly possible to arrange buses
       since it comes intuitively that all t >= c will also allow us to arrange buses and all t < c will not

    thus, we can use binary search to find the time difference c
    which is the least maximum wait time a cow will have to experience
    */

    ifstream fin("convention.in");
    ofstream fout("convention.out");

    fin >> n >> m >> bus_capacity;
    vector<int> arrival_times(n);
    for (int& time : arrival_times) {
        fin >> time;
    }
    sort(arrival_times.begin(), arrival_times.end());

    long long low = 0, high = (long long) arrival_times[n - 1] - arrival_times[0] + 1;
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (can_arrange(mid, arrival_times)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    fout << low;
}
