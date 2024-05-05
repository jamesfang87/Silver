#include <bits/stdc++.h>
using namespace std;


int main() {
    ifstream in("cardgame.in");
    ofstream out("cardgame.out");

    int n; in >> n;
    vector<bool> taken(n * 2, false);
    vector<int> elise(n);
    for (int i = 0; i < n; i++) {
        int temp; in >> temp;
        taken[temp - 1] = true;
        elise[i] = temp;
    }

    vector<int> bessie;
    for (int i = 0; i < n * 2; i++) {
        if (!taken[i])
            bessie.push_back(i + 1);
    }

    sort(elise.begin(), elise.begin() + n / 2);
    sort(elise.begin() + n / 2, elise.end());
    
    int b, e, ans = 0;

    // instead of using set::upper_bound/set::lower_bound, we can use two pointers since array is sorted
    // order we process the sides does not matter
    // the location our starting pointers are at do matter because arrays are sorted
    
    // solve first half of game
    // want to have a bigger card
    b = n / 2, e = 0;
    while (e < n / 2) {
        while (bessie[b] < elise[e] && b < n) {
            b++;
        }

        if (b == n)
            break;

        ans++; e++; b++;
    }

    // solve second half of game
    // want a smaller card
    b = n / 2 - 1, e = n - 1;
    while (e >= n / 2) {
        while (bessie[b] > elise[e] && b >= 0) {
            b--;
        }

        if (b == -1)
            break;

        ans++; e--; b--;
    }

    out << ans;
}