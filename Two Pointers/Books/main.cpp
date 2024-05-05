#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, a; cin >> n >> a;

    int books[n];
    for (int i = 0; i < n; i++) {
        cin >> books[i];
    }

    int l_ptr = 0, r_ptr = 0, ans = 0, sum = 0;
    while (l_ptr < n && r_ptr < n) {
        while (r_ptr < n) {
            sum += books[r_ptr];
            r_ptr++;


            if (sum > a) {
                sum -= books[r_ptr - 1];
                r_ptr--;
                break;
            }
        }

        ans = max(ans, r_ptr - l_ptr);

        sum -= books[l_ptr];
        l_ptr++;
    }
    cout << ans;
}
