#include <iostream>
using namespace std;

void solve(string garland) {
    int total_edits; char fav_color;
    cin >> total_edits >> fav_color;

    int start = 0, end = 0;
    int used_edits = 0;
    int ans = INT_MIN;
    for (; start < garland.length(); start++) {
        // use up all edits
        while (end < garland.length() && used_edits < total_edits) {
            if (garland[end] != fav_color) {
                used_edits++;
            }
            end++;
        }
        
        // sometimes we have used all edits but have connected two segments of fav colors
        // take this into account
        while (end < garland.length() && garland[end] == fav_color) {
            end++;
        }

        ans = max(ans, end - start);
        
        if (garland[start] != fav_color) {
            used_edits--;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int len; string garland;
    cin >> len >> garland;

    int t; cin >> t;
    while (t--) {
        solve(garland);
    }
}
