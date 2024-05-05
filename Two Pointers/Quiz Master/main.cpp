#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

int solve() {
    int n, m; cin >> n >> m;
    vector<int> smartness(n), team;
    for (int i = 0; i < n; i++) {
        cin >> smartness[i];
    }
    sort(smartness.begin(), smartness.end());


    // minimize the number of students in the team
    // try to go linearly from a student

    // start from the largest prime number
    // 1 can be any number, and we can fill it in later
    // choose the first student divisible by T
    // once we find a student that is proficient at topic T,
    // all multiples of T can be covered by that student
    // prime numbers require another student
    // every other number can be covered by a previous prime number

    unordered_map<int, int> topics;
    for (int i = 2; i <= m; i++) {
        if (topics[i] == 0) {
            // new prime number
            // generate best student
            int best_student = 0;
            // populate multiples
            int multiple = i;
            while (multiple < m) {
                topics[m] = best_student;
            }

            team.push_back(best_student);
        } else {
            // multiple of a previously seen prime
            // don't have to do anything
        }
    }

    int minimum = *min_element(team.begin(), team.end());
    int maximum = *max_element(team.begin(), team.end());
    return maximum - minimum;
}

int main() {
    int t; cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
}