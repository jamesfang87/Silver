#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;
 
typedef long long i64;
i64 n;
 
struct Carriage {
    i64 start, end, index;
};
 
bool possible(i64 m, vector<i64> passengers, const vector<Carriage> &carriages) {
    auto c_ptr = carriages.begin();

    // .first = end, .second = amt
    priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, greater<pair<i64, i64>>> active; // active pool of passengers
    vector<pair<int, int>> processed; 
    for (int i = 0; i < n; i++) {
        // remove carriages that we have gone past
        while (!active.empty() && active.top().first < i) {
            processed.push_back(active.top());
            active.pop();
        }
 
        // then add carriages that we have just entered
        // by 'taking out' the passengers in the carriage
        while (c_ptr != carriages.end() && c_ptr->start <= i) {
            active.push({c_ptr->end, passengers[c_ptr->index]});
            passengers[c_ptr->index] = 0;

            c_ptr++;
        }
 
        // now try to give this carriage m people
        // assume, that the carriage is empty,
        // since we take out it's passengers
        while (!active.empty() && passengers[i] < m) {
            auto [end, amt] = active.top();
            active.pop();
 
            if (passengers[i] + amt < m) {
                passengers[i] += amt;
            } else {
                active.push({end, amt - (m - passengers[i])});
                passengers[i] = m;
            }
        }

        if (passengers[i] > m) {
            return false;
        }
    }
    
    while (!active.empty()) {
        processed.push_back(active.top());
        active.pop();
    }

    for (auto& p : processed) {
        if (p.second != 0) {
            return false;
        }
    }
    return true;
}
 
int main() {
    cin >> n;
    vector<i64> passengers(n);
    for (i64 &p : passengers) {
        cin >> p;
    }
 
    vector<Carriage> carriages;
    for (int i = 0; i < n; i++) {
        i64 r; cin >> r;
        if (passengers[i] != 0 && r != 0)
            carriages.push_back({max(0ll, (i64)i - r), min(n - 1, (i64)i + r), i});
    }
    sort(carriages.begin(), carriages.end(), [&](Carriage &lhs, Carriage &rhs) {
        return tie(lhs.start, lhs.end, lhs.index) < tie(rhs.start, rhs.end, rhs.index);
    });

    i64 l = accumulate(passengers.begin(), passengers.end(), 0) / n, r = (i64)1e9 + 1;
    while (l < r) {
        i64 m = l + (r - l) / 2;
        if (possible(m, passengers, carriages)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << '\n';
}