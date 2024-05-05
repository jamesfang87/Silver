#include <iostream>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n; cin >> x >> n;
    set<int> traffic_lights = {0, x};
    multiset<int> segment_lens = {x};
    for (int i = 0; i < n; i++) {
        int traffic_light; cin >> traffic_light;

        auto original_end = traffic_lights.upper_bound(traffic_light);
        auto original_start = prev(original_end);

        int len = *original_end - *original_start;
        segment_lens.erase(segment_lens.find(len));

        segment_lens.insert(traffic_light - *original_start);
        segment_lens.insert(*original_end - traffic_light);
        traffic_lights.insert(traffic_light);

        cout << *segment_lens.rbegin() << ' ';
    }
}