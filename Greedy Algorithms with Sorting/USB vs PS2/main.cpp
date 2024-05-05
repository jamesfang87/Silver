#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
    int count[3];
    cin >> count[0] >> count[1] >> count[2];
    int n; cin >> n;

    pair<int, int> mice[n];
    for (auto& m : mice) {
        string type; cin >> m.first >> type;
        m.second = type != "USB";
    }

    // we should try to buy the cheapest mice possible
    sort(mice, mice + n);

    int ans = 0; long long cost = 0;
    for (auto m : mice) {
        // we want to try to fill up the computers that only have one port
        if (count[m.second] > 0) {
            count[m.second]--;
            ans++; cost += m.first;
        } else if (count[2] > 0) {
            count[2]--;
            ans++; cost += m.first;
        }
    }
    cout << ans << " "<< cost;
}
