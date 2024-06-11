#include <cmath>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#define all(x) x.begin(), x.end()

int num_cows, num_intervals;

bool possible(long long dist, std::vector<long long> grass_intervals) {
    int cows_left = num_cows - 1; // we automatically place a cow at the first avaliable position
    int cur_interval = 0;
    long long cur_location = grass_intervals[0]; // place the first cow at the first avaliable position
    while (cows_left--) {
        // calculate the potential location candidate: distance d away from the "current location"
        long long potential_location = cur_location + dist;

        // if the potential location is outside the most rightward interval, then return false
        if (potential_location > grass_intervals[grass_intervals.size() - 1]) {
            return false;
        }

        // otherwise, we check if we can put a cow at our potential location
        // find the point immediately more rightward than our potential location
        int index = std::upper_bound(all(grass_intervals), potential_location) - grass_intervals.begin();
        if (grass_intervals[index - 1] == potential_location) {
            // valid location at an endpoint of an interval
            cur_location = potential_location;
        } else if (index % 2 == 1 && grass_intervals[index - 1] < potential_location && potential_location < grass_intervals[index]) {
            // valid location inside an interval
            cur_location = potential_location;
        } else {
            // invalid location when our potential location is between two intervals
            // ...end] potential location [start...
            // we simply set the cow at the start of the next interval of grass
            cur_location = grass_intervals[index];
        }
    }
    return true;
}

int main() {
    /*
    notice that if our d is small enough, we can fit every cow into the intervals
    with a gap d between any two pairs of cows
    however, if d is too large, we cannot fit every cow into the intervals

    thus, we can use binary search to find the largest distance d
    which we can still fit every cow into the intervals

    now, we simply have to create a method to quickly determine
    whether we can fit every cow into the intervals or not

    for an arbitrary cow i:
    assign a pointer to the first free space of grass possible and place the cow there
    then update the pointer: if the location distance d away has grass, advance the pointer there
    otherwise, put the pointer at the start of the next interval
    */
    std::ifstream fin("socdist.in");
    std::ofstream fout("socdist.out");

    fin >> num_cows >> num_intervals;

    std::vector<long long> grass_intervals(num_intervals * 2);
    for (auto& point : grass_intervals) {
        fin >> point;
    }
    std::sort(grass_intervals.begin(), grass_intervals.end());

    long long min_dist = 0, max_dist = grass_intervals[2 * num_intervals  - 1] - grass_intervals[0];
    while (min_dist < max_dist) {
        long long mid_dist = min_dist + (max_dist - min_dist + 1) / 2;
        if (possible(mid_dist, grass_intervals)) {
            min_dist = mid_dist;
        } else {
            max_dist = mid_dist - 1;
        }
    }
    fout << min_dist;
}
