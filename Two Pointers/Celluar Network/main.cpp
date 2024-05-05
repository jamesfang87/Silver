#include <iostream>

using namespace std;

int main() {
    int n, m; cin >> n >> m;

    int cities[n], towers[m];

    for (int i = 0; i < n; i++) {
        cin >> cities[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> towers[i];
    }

    int ans = INT32_MIN;

    int tower_ptr = 0;
    for (int city_ptr = 0; city_ptr < n; city_ptr++) {
        int temp = INT32_MAX;

        if (tower_ptr > 0 && towers[tower_ptr] > cities[city_ptr]) {
            tower_ptr--;
        }

        while (tower_ptr < m - 1 && towers[tower_ptr] <= cities[city_ptr]) {
            temp = min(temp, abs(towers[tower_ptr] - cities[city_ptr]));
            tower_ptr++;
        }

        ans = max(ans, min(temp, abs(towers[tower_ptr] - cities[city_ptr])));
    }

    cout << ans;

}
