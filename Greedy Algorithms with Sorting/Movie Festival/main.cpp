#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
    int n; cin >> n;
    pair<int, int> movies[n];

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        movies[i] = {b, a};
    }

    sort(movies, movies + n);

    int ans = 0, cur_time = 0;
    for (int i = 0; i < n; i++) {
        if (cur_time <= movies[i].second) {
            ans++;
            cur_time = movies[i].first;
        }
    }

    cout << ans;
}