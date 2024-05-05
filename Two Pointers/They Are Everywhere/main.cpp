#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {
    int n; cin >> n;
    string flats; cin >> flats;
    int num_unique;
    unordered_set<char> unique;
    for (int i = 0; i < n; i++) {
        unique.insert(flats[i]);
    }
    num_unique = unique.size();
    int l_ptr = 0, r_ptr = 0;

    unordered_map<char, int> collected; int num_collected = 0;
    int ans = INT32_MAX;
    while (l_ptr < n && r_ptr < n) {
        while (num_collected < num_unique && r_ptr < n) {
            if (collected[flats[r_ptr]] == 0) {
                num_collected++;
            }
            collected[flats[r_ptr]] += 1;
            r_ptr++;
        }

        while (num_collected == num_unique && l_ptr < r_ptr) {
            collected[flats[l_ptr]]--;
            if (collected[flats[l_ptr]] == 0) {
                num_collected--;
            }
            l_ptr++;
        }

        ans = min(ans, (r_ptr - l_ptr + 1));
    }

    cout << ans;
}
