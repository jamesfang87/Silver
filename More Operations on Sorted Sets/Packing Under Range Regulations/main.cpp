#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
using namespace std;

void solve() {
    // this question is similar to the greedy algorithm for maximizing the amount of
    // events participated in: sort by the end time (right bound in this case)
    // start from box 1 and try to fill each box
    // the box we choose is the one with the smallest right bound
    int n; cin >> n;

    unordered_map<int, vector<int>> starting_at;
    set<int> starts;
    for (int i = 0; i < n; i++) {
        int left, right; cin >> left >> right;

        starting_at[left].push_back(right);
        starts.insert(left);
    }
    starts.insert(1000000001);

    bool possible = true;
    priority_queue<int, vector<int>, greater<>> valid_balls;
    int i = *starts.begin();
    while (i <= 1000000000) {
        // add all balls with their valid range starting at i to the prioq
        // these are the balls that are newly available
        for (int ball : starting_at[i]) {
            valid_balls.push(ball);
        }

        // remove the ball with the lowest end to its valid range
        // this is the ball we put in box i
        valid_balls.pop();

        if (valid_balls.empty()) {
            // there will be large gaps between starts
            // we can skip these gaps using .lower_bound
            i = *starts.lower_bound(i + 1);
        } else if (valid_balls.top() <= i) {
            // we ran out of boxes to put this ball in
            // the rightmost index the ball can be put in is past
            possible = false;
            break;
        } else {
            i++;
        }
    }

    // if there are balls which we can't put into boxes, it is not possible
    if (!valid_balls.empty()) {
        possible = false;
    }

    if (possible) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}