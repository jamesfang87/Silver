#include <fstream>
#include <algorithm>
#include <utility>
using namespace std;



int main() {
    ifstream in("diamond.in");
    ofstream out("diamond.out");
    int n, k; in >> n >> k;
    int sizes[n];
    for (int &s : sizes) {
        in >> s;
    }
    sort(sizes, sizes + n);

    int max_before_line[n], max_after_line[n];
    int l = 0, r = 0;
    for (; l < n; l++) {
        while (r < n && sizes[r] - sizes[l] <= k) {
            if (r > 0) {
                max_before_line[r] = max(max_before_line[r - 1], r - l + 1);
            } else {
                max_before_line[r] = r - l + 1;
            }
            r++;
        }
    }

    r = n - 1; l = n - 1;
    for (; r >= 0; r--) {
        while (l >= 0 && sizes[r] - sizes[l] <= k) {
            if (l < n - 1) {
                max_after_line[l] = max(r - l + 1, max_after_line[l + 1]);
            } else {
                max_after_line[l] = r - l + 1;
            }
            l--;
        }
    }

    int ans = INT32_MIN;
    for (int i = 0; i < n - 1; i++) {
        // split the diamonds into 2 groups

        // find the largest subarray before i
        // find the largest subarray starting at or after i

        // add their lengths
        ans = max(ans, max_before_line[i] + max_after_line[i + 1]);
    }

    out << ans;
}