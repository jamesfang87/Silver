#include <bits/stdc++.h>
using namespace std;

struct Cow {
    int weight, pos, direction;

    // think about the collision as the cows switching weights
    // since their position is the same at a collision and they just invert directions
    // that way we can think of meetings as the swaping weights and travelling in the same direction

    bool operator < (const Cow& other) const {
        return pos < other.pos;
    }
};

int main() {
    ifstream fin("meetings.in");
    ofstream fout("meetings.out");

    int num_cows = -1, total_weight = 0;
    int left_barn = 0, right_barn = -1; // place holder value for num cows and right barn
    fin >> num_cows >> right_barn;


    vector<Cow> cows(num_cows);
    for (Cow& c : cows) {
        fin >> c.weight >> c.pos >> c.direction;
        total_weight += c.weight;
    }
    sort(cows.begin(), cows.end());

    // split the cows into vectors based on direction
    vector<Cow> left_going, right_going;
    for (Cow c : cows) {
        if (c.direction == -1) {
            left_going.push_back(c);
        } else {
            right_going.push_back(c);
        }
    }

    // information about each cow stopping: .first = arrival time at barn, .second = weight that the cow contributes
    vector<pair<int, int>> stopping_info;

    // n-th left-moving cow gains the weight of the n-th most leftward cow overall
    for (int i = 0; i < left_going.size(); i++) {
        int arrival_time = left_going[i].pos - left_barn;
        stopping_info.push_back({arrival_time, cows[i].weight});
    }

    // n-th right-moving cow gains the weight of the n-th most rightward cow overall
    for (int i = 0; i < right_going.size(); i++) {
        // reverse index since right side is sorted in increasing order of position (most leftward first)
        int arrival_time = right_barn - right_going[right_going.size() - i - 1].pos;
        stopping_info.push_back({arrival_time, cows[num_cows - i - 1].weight});
    }

    // sort by time
    sort(stopping_info.begin(), stopping_info.end());

    int half_time; // time T in problem statement
    int cur_weight = 0;
    for (auto& [time, weight] : stopping_info) {
        // i love auto& [name1, name2] for pairs <3 thank u c++
        cur_weight += weight;
        // flip the 2 so we can deal with integers
        if (cur_weight * 2 >= total_weight ) {
            half_time = time;
            break;
        }
    }

    int ans = 0; // number of meetings before half time
    // loop through all the leftward cows and check if they can meet rightward moving cows before half time
    // this can also be done by looping over rightward cows
    queue<Cow> q; // holds rightward moving cows
    for (Cow c : cows) {
        if (c.direction == 1) {
            q.push(c);
        } else {
            // check how many cows in the queue that this left moving cow can hold
            // note that cows to the right of a left moving cow can not meet the left moving cow

            // delta x = vt -> delta x / v = t; if we set our frame of reference onto one cow, the other has a v of 2
            while (!q.empty()) {
                int collision_time = abs(c.pos - q.front().pos); // division by 2 (velocity) moved to condition to have only ints
                if (collision_time > 2 * half_time) {
                    q.pop();
                } else {
                    ans += q.size();
                    break;
                }
            }   
        }
    }
    fout << ans;
}
