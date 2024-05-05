#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Cow {
    int arrival_time, time_eating, seniority;
};

bool sort_by_time(const Cow& a, const Cow& b) {
    return a.arrival_time < b.arrival_time;
}

class sort_by_seniority {
public:
    bool operator() (Cow a, Cow b) {
        return a.seniority > b.seniority;
    }
};


int main() {
    ifstream fin("convention2.in");
    ofstream fout("convention2.out");
    int n; fin >> n;

    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        fin >> cows[i].arrival_time >> cows[i].time_eating;
        cows[i].seniority = i;
    }

    sort(cows.begin(), cows.end(), sort_by_time);

    // move the nth cow to the field
    // advance through the array of cows
    // if the cow arrives before the cow on the field finishes
    // add to a pq sorted based on seniority
    // when the nth cow finishes, pop the top cow off the pq and move it to the field
    // calculate wait time with current time - arrival time and update ans

    Cow current_cow = cows[0];
    long long current_time = current_cow.arrival_time;
    long long finish_time = current_time + current_cow.time_eating;
    priority_queue<Cow, vector<Cow>, sort_by_seniority> pq;
    long long ans = INT64_MIN;

    int i = 1;
    while (i < n) {
        if (cows[i].arrival_time <= finish_time) {
            pq.push(cows[i]);
            i++;
        } else {
            if (!pq.empty()) {
                current_time = finish_time;
                current_cow = pq.top(); pq.pop();

                long long wait_time = current_time - current_cow.arrival_time;
                ans = max(ans, wait_time);

                finish_time = current_cow.time_eating + current_time;
            } else {
                current_time = cows[i].arrival_time;
                finish_time = current_time + cows[i].time_eating;
                i++;
            }
        }
    }

    current_time = finish_time;
    current_cow = pq.top(); pq.pop();

    long long wait_time = current_time - current_cow.arrival_time;
    ans = max(ans, wait_time);

    fout << ans;
}
