#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main() {
    ifstream fin("herding.in");
    ofstream fout("herding.out");

    int n; fin >> n;
    vector<int> locations(n);
    for (int& location : locations) {
        fin >> location;
    }
    // sort the cows to make them easier to work with
    sort(locations.begin(), locations.end());

    // rules:
    // can only move 2 cows at a time, the endpoints
    // cannot be moved to any occupied location and another endpoint


    // minimum number of moves
    // find a window with length n with the least amount of gaps
    // length refers to difference between the position of cows, not the number of cows
    // this optimal since we can always fill in the gaps with just the number of cows needed
    if ((locations[n - 2] - locations[0] == n - 2 && locations[n - 1] - locations[n - 2] > 2) ||
        (locations[n - 1] - locations[1] == n - 2 && locations[1] - locations[0] > 2)) {
        fout << "2\n";
    } else {
        int min_moves = INT32_MAX; // the number of gaps, which is the answer: the minimum number of moves needed
        int left = 0, right = 1;
        for (; left < n; left++) {
            // while right is in range and length of the window is less than n
            while (right < n && locations[right] - locations[left] < n) {
                right++;
            }
            // if there are no gaps, then right - left == n (the max value that right can be is n)
            // this is an "exception" since right is technically out of range
            
            // otherwise, right - left < n and locations[right] - locations[left] == n
            // there are locations[right] - locations[left] - 1 = n - 1 in between
            // there are right - left - 1 cows in between
            // thus, the number of empty spots is n - 1 - (right - left - 1)
            // n - 1 - (right - left - 1) = n - 1 - right + left + 1
            //                            = n - right + left
            //                            = n - (right - left)
            min_moves = min(min_moves, n - (right - left));
        }
        fout << min_moves << '\n';
    }

    // maximum number of moves
    int num_gaps = 0;
    for (int i = 1; i < n; i++) {
        num_gaps += locations[i] - locations[i - 1] - 1;
    }

    // idea to maximize the number of moves is to move endpoint cows to
    // empty spots in the opposite side:
    // the cow at the right endpoint to the leftmost empty spot
    // the cow at the left endpoint to the rightmost empty spot

    // for all moves except the first, we can fill in an empty spot
    // but for the first move, we have to get rid of either the leftmost or rightmost gap
    // the answer is thus num_gaps - min(leftmost gap, rightmost gap)

    int leftmost_gap = locations[1] - locations[0] - 1;
    int rightmost_gap = locations[n - 1] - locations[n - 2] - 1;
    fout << num_gaps - min(leftmost_gap, rightmost_gap);
}
