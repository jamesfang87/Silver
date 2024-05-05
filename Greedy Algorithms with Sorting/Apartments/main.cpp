#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k;

    int applicants[n], apartments[m];

    for (int& a: applicants) {
        cin >> a;
    }

    for (int& a: apartments) {
        cin >> a;
    }

    sort(applicants, applicants + n);
    sort(apartments, apartments + m);

    int applicant = 0, apartment = 0, ans = 0;
    while (applicant < n && apartment < m) {
        int difference = apartments[apartment] - applicants[applicant];
        if (abs(difference) <= k) {
            ans++;
            apartment++; // increment apartment ptr
            applicant++; // move to next applicant
        } else if (difference > k) {
            applicant++;
        } else if (difference < -1 * k) {
            apartment++;
        }
    }

    cout << ans;
}
