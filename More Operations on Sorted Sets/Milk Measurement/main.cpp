#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;

struct Log {
    int day, cow, change;
};

bool cmp(Log l1, Log l2) {
    return l1.day < l2.day;
}

int main() {
    ifstream fin("measurement.in");
    ofstream fout("measurement.out");

    int n, g; fin >> n >> g;

    vector<Log> logs(n);
    for (auto& log : logs) {
        fin >> log.day >> log.cow >> log.change;
    }
    sort(logs.begin(), logs.end(), cmp);

    unordered_map<int, int> produced;
    int changes = 0;

    // num cows who hold produce a certain amount of milk
    // .first -> amount of milk .second -> number of cows;
    map<int, int> num_cows = {{0, n}};
    for (auto log : logs) {
        // amount produced before and after measurement
        int original_amount = produced[log.cow];
        int changed_amount = original_amount + log.change;

        // if the cow is one of those on the leaderboard
        // cows can be on leaderboard if they were originally on it at the time of last measurement
        // or if they surpassed or met the leaderboard cutoff.
        int leaderboard_cutoff = num_cows.rbegin()->first;
        int prev_leaderboard_population = num_cows[leaderboard_cutoff];
        bool was_on_leaderboard = (original_amount == leaderboard_cutoff);


        // change information stored in ds
        num_cows[original_amount]--;
        if (num_cows[original_amount] == 0)
            num_cows.erase(original_amount);
        num_cows[changed_amount]++;
        produced[log.cow] = changed_amount;

        int cur_leaderboard_population = num_cows.rbegin()->second;
        bool on_leaderboard = (changed_amount == num_cows.rbegin()->first);

        // changes happen when
        // a cow who wasn't on the leaderboard now is
        // a cow who was on the leaderboard now produces more than the previous maximum
        // when a cow on the leaderboard falls off

        if (was_on_leaderboard) {
            // there is a situation where one cow is the sole cow on the leaderboard
            // then gains or loses some milk while remaining the sole cow on the leaderboard
            if (on_leaderboard &&
                prev_leaderboard_population == 1 &&
                cur_leaderboard_population == 1) {
                continue;
            }
            changes++;
        } else if (on_leaderboard) {
            changes++;
        }
    }
    fout << changes;
}
