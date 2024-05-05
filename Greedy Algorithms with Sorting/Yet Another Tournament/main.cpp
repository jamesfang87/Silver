#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve() {
    int n, m;
    cin >> n >> m;

    vector<int> prep_times(n);
    for (auto &time : prep_times)
        cin >> time;

    auto placements = prep_times;
    std::reverse(placements.begin(), placements.end());
    sort(prep_times.begin(), prep_times.end());

    // we want to maximize the number of wins we get
    int wins = 0; int largest = 0;
    for (int i = 0; i < n; i++) {
        if (prep_times[i] > m) {
            largest = prep_times[i - 1];
            break;
        }

        m -= prep_times[i];
        wins++;
    }

    // there can be another contest with place i with the same
    // amount of wins as us (i = wins)
    // instead of losing to them, we choose to prep for them
    // so we can tie with the same amount of wins
    // improving rank by 1

    // place is n - wins: with 0 wins and n = 4, place = 4
    int place = n - wins; // 0-indexed
    // we cannot change our place if we are first or last (where we cannot beat anyone)
    if (place != 0 && place != n) {
        // if we can beat the contestant ahead of us instead (place - 1 since lower is better)
        // by spending time preparing for them, we can go up 1 in rank
        if (m + largest >= placements[place - 1]) {
            place--;
        }
    }

    return place + 1; // return 1-indexed placement
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
}