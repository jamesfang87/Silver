#include <fstream>
using namespace std;

int main() {
    ifstream fin("reststops.in");
    ofstream fout("reststops.out");
    int l, n, fj_speed, bessie_speed;
    fin >> l >> n >> fj_speed >> bessie_speed;

    // first = location, second = reward
    vector<pair<int, int>> rest_stops(n);
    for (int i = 0; i < n; i++) {
        fin >> rest_stops[i].first >> rest_stops[i].second;
    }

    sort(rest_stops.begin(), rest_stops.end(), greater<>());

    // bessie and farmer john should reach the end at the same time
    // the time bessie has to eat grass is maximized


    vector<pair<int, int>> stops; int maximum = -1;
    for (int i = 0; i < n; i++) {
        if (rest_stops[i].second > maximum) {
            maximum = rest_stops[i].second;
            stops.insert(stops.begin(), rest_stops[i]);
        }
    }

    // bessie can eat for as much time as it takes for farmer john to reach the patch
    long long ans = 0, last_synchronized = 0;
    for (auto stop : stops) {
        ans += (fj_speed - bessie_speed) * (stop.first - last_synchronized) * stop.second;
        last_synchronized = stop.first;
    }
    fout << ans;
}
