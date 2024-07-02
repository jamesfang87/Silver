#include <bits/stdc++.h>
using namespace std;

int main() {
    // fast io
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n; cin >> n;
    int values[n], colors[n];

    for (int& v : values) cin >> v;
    for (int& c : colors) cin >> c;

    /*
    notice that all operations deal with only elements of a certain colors
    therefore, it much easier to split the array into subsequences of the same colors

    we should have enough memory to use an array- bonus of faster lookups
    */

    // prefix sums for each colors
    vector<long long> prefix_sums[200001]; // size 200001 to allow for use of 1-indexed colors
    for (int i = 0; i < n; i++) {
        long long last_prefix;
        if (prefix_sums[colors[i]].empty()) {
            last_prefix = 0;
        } else {
            last_prefix = prefix_sums[colors[i]].back();
        }
 
        prefix_sums[colors[i]].push_back(last_prefix + values[i]);
    }

    /*
    it would be far too slow to update the prefix sums array for each color
    thus we can have an array storing the amount not added for each color
    as well as a single long long storing the total amount added by type 1 queries
    thus, we can add (total_added - amount_excluded[color]) to find the
    amount added to each element of color. this works in constant time
    */

    // the amount NOT added for each colors by type 1 queries
    long long amount_excluded[200001];
    memset(amount_excluded, 0, sizeof amount_excluded); // memset to 0
    // the total amount added by type 1 queries
    long long total_added = 0;

	int q; cin >> q;
	while (q--) {
		int type, color;
        long long val; // will overflow if not long long
		cin >> type >> color >> val;

		if (type == 1) {
			total_added += val;
			amount_excluded[color] += val;
		} else {
            // binary search on the prefix length
			int low = -1, high = prefix_sums[color].size() - 1;
			while (low < high) {
				int mid = low + (high - low + 1) / 2;
				long long total_offset = (total_added - amount_excluded[color]) * (mid + 1);
				if (prefix_sums[color][mid] + total_offset <= val) {
					low = mid;
				} else {
					high = mid - 1;
				}
			}
			std::cout << low + 1 << '\n';
		}
	}
}