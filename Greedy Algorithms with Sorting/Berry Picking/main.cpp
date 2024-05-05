#include <fstream>
using namespace std;

int main() {
    ifstream in("berries.in");
    ofstream out("berries.out");

    int n, k; in >> n >> k;
    int m = 0;
    int trees[n];
    for (int& t : trees) {
        in >> t;
        m = max(t, m);
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        // we take multiples of "i" berries from each tree, as much as we can
        // and fill as many berries as we can

        int filled_baskets = 0;
        for (int t : trees) {
            filled_baskets += t / i;
        }
        // if we can't fill more than k/2 berries, our "i" is too big and we stop searching
        if (filled_baskets <= k / 2) {
            break;
        }

        // if we can fit k or more baskets, update our answer
        if (filled_baskets >= k) {
            ans = max(ans, k / 2 * i);
            continue;
        }

        // otherwise, we must consider our leftover berries.
        // sort each tree by the number of berries remaining: a mod i
        // and pick all berries
        sort(trees, trees + n, [&i](int a, int b) { return a % i > b % i; });
        int cur = (filled_baskets - k / 2) * i, t = 0, baskets_left = k - filled_baskets;
        while (baskets_left > 0 && t < n) {
            cur += trees[t++] % i;
            baskets_left--;
        }
        ans = max(cur, ans);
    }
    out << ans;
}