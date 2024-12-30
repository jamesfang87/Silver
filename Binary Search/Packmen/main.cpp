#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> food_pos, packmen_pos;

bool possible(int t) {
    auto first_uneaten = food_pos.begin();

    // every packman attempts to eat the leftmost uneaten asterisk
    for (int packman : packmen_pos) {
        if (*first_uneaten < packman) {
            // standard case where the leftmost uneaten asterisk is to the left of the packman

            // calculate the amount of time it takes to reach this asterisk
            int time_needed = packman - *first_uneaten;
            // check that this time doesn't exceed t, return false if so
            if (time_needed > t) {
                return false;
            }

            // since there may be some extra time at the end
            // check if we can eat some closeby asterisks on the right side

            // however, there is a caveat: sometimes we can eat more
            // if we move to the right side first
            // ex: **.P**** where time limit = 7
            // if we move to the left first, we can only eat 3
            // if we move to the right first, we can eat 4

            // first move the iterator since we will be eating the left asterisks anyways
            while (first_uneaten != food_pos.end() && *first_uneaten < packman) {
                first_uneaten++;
            }

            // check moving to the left first
            int left = 0;
            int free_time = t - 2 * time_needed;
            auto temp = first_uneaten;
            while (temp != food_pos.end() && *temp <= packman + free_time) {
                temp++;
                left++;
            }

            // now check moving to the right
            // add a div or mul by 2
            int right = 0;
            free_time = t - time_needed;
            temp = first_uneaten;
            while (temp != food_pos.end() && (*temp - packman) * 2 <= free_time) {
                temp++;
                right++;
            }

            // eat the remaining asterisks on the right
            for (int i = 0; i < max(left, right); i++) {
                first_uneaten++;
            }
        } else {
            // if the leftmost uneaten asterisk is to the right,
            // then there are no asterisks to the left of this packman
            // thus, we want to just go as far right as possible
            while (first_uneaten != food_pos.end() && *first_uneaten <= packman + t) {
                first_uneaten++;
            }
        }

        // check that all asterisks have been eaten
        if (first_uneaten == food_pos.end()) {
            return true;
        }
    }

    return (first_uneaten == food_pos.end());
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        char s;
        cin >> s;
        if (s == '*') {
            food_pos.push_back(i);
        } else if (s == 'P') {
            packmen_pos.push_back(i);
        }
    }

    sort(food_pos.begin(), food_pos.end());
    sort(packmen_pos.begin(), packmen_pos.end());

    int l = 0, r = INT32_MAX;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (possible(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << '\n';
}
