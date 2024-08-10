/*
It’s hard to directly binary search on the maximum power, p, 
such that it can be constructed with m handshakes. 
Instead, it is easier to think about how to construct p. 
Consider the amount that the total power at least increases by per handshake, p’. 
Given this lower bound on the amount of power gained per handshake, 
we can “filter” the total n^2 handshakes, discarding the ones that give less power than p’ 
and figuring out how many valid handshakes still exist. 
We can binary search on the maximum value for p’ such that we can still perform m handshakes.
After we find this value for p’, we can construct the answer using prefix sums and a similar process.

However, there is the case where there is no value of p' such that there are exactly m valid handshakes
In this case, it is sufficient to count the total number valid handshakes which are added to our ans
and then subtract the difference: (valid_handshakes - m) * p'
*/
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long i64;

i64 n, m;
i64 guests[100000], suf[100001];

i64 last_valid_handshake(i64 threshold, int guest_id) {
    // the last valid handshake found using binary search
    int l = 0, r = n;
	while (l < r) {
		int ptr = l + (r - l) / 2;
		if (guests[guest_id] + guests[ptr] >= threshold) {
			r = ptr;
		} else {
			l = ptr + 1;
		}
	}
	return l;
}

i64 get_num_handshakes(i64 threshold) {
	i64 total_handshakes = 0;
	for (int i = 0; i < n; i++) {
		total_handshakes += n - last_valid_handshake(threshold, i);
	}
	return total_handshakes;
}

int main() {
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) {
	    cin >> guests[i];
	}

	sort(guests, guests + n);
	
	for (int i = n - 1; i >= 0; i--) {
	    suf[i] = suf[i + 1] + guests[i];
	}
	
	i64 l = 0, r = guests[n - 1] * 2;
	while (l < r) {
	    i64 mid = l + (r - l + 1) / 2;
		if (get_num_handshakes(mid) >= m) {
		    l = mid;
		} else {
		    r = mid - 1;
		}
	}
	
	i64 threshold = l;
	i64 ans = 0, total_handshakes = 0;
	for (int i = 0; i < n; i++) {
	    i64 temp = last_valid_handshake(threshold, i);
        total_handshakes += n - temp;
		ans += suf[temp] + guests[i] * (n - temp);
	}
	cout << ans - ((total_handshakes - m) * threshold);
}
