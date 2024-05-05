#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>


struct Event {
    int time;
    int cow;
    std::string action;
};

bool cmp(const Event& e1, const Event& e2) {
    return e1.time < e2.time;
}


int main() {
    std::fstream in("lifeguards.in");
    std::ofstream out("lifeguards.out");
    int n; in >> n;

    Event events[n * 2];
    for (int i = 0; i < n * 2; i += 2) {
        int start, end;
        in >> start >> end;
        events[i] = {start, i / 2, "enter"};
        events[i + 1] = {end, i / 2, "leave"};
    }

    std::sort(events, events + n * 2, cmp);

    std::set<int> active_lifeguards = {};
    std::vector<int> alone_time (n, 0);

    int total_time = 0;
    int prev_time = events[0].time;
    for (int i = 0; i < n * 2; i++) {
        if (active_lifeguards.size() == 1) {
            alone_time[*active_lifeguards.begin()] = events[i].time - prev_time;

        }
        if (!active_lifeguards.empty()) {
            total_time += events[i].time - prev_time;
        }
        prev_time = events[i].time;

        if (events[i].action == "enter") {
            active_lifeguards.insert(events[i].cow);
        } else {
            active_lifeguards.erase(events[i].cow);
        }
    }
    out << total_time - *std::min_element(alone_time.begin(), alone_time.end());
}
