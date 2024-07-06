#include <bits/stdc++.h>
using namespace std;


struct Update {
    int left, right, amount;
};

int main() {
    int n, m, k; cin >> n >> m >> k;

    vector<int> array(n);
    for (int& a : array) {
        cin >> a;
    }

    vector<Update> updates(m);
    for (Update& u : updates) {
        cin >> u.left >> u.right >> u.amount;
        u.left--; u.right--;
    }

    // the amount of times each update operation is applied
    // last value is unused
    vector<long long> times_applied(m + 1, 0);
    for (int i = 0; i < k; i++) {
        // apply all operations between and including first and last operation
        int first_operation, last_operation;
        cin >> first_operation >> last_operation;

        // we can use a difference array to efficiently count how many times
        // each operation is applied
        
        // operations are 1-indexed so this differs from how difference arrays are normally set up: 
        // times_applied[first_operation]++;
        // times_applied[last_operation + 1]--;
        times_applied[first_operation - 1]++;
        times_applied[last_operation]--;
    }
    
    // we can merge the first 2 loops together and last 2 loops together
    // to make this code run faster (since we are repeating computation)

    // run a prefix sums to build times_applied array
    for (int i = 1; i < m; i++) {
        times_applied[i] += times_applied[i - 1];
    }

    // the amount added to each element in the array
    vector<long long> added(n + 1, 0); // last value is unused
    for (int i = 0; i < m; i++) {
        Update u = updates[i];

        // u.left and u.right are already 0-indexed so we can keep using
        // the standard way to build a difference array
        added[u.left] += u.amount * times_applied[i];
        added[u.right + 1] -= u.amount * times_applied[i];
    }

    // run a prefix sums to build added array
    for (int i = 1; i < n; i++) {
        added[i] += added[i - 1];
    }

    for (int i = 0; i < n; i++) {
        cout << array[i] + added[i] << ' ';
    }
}
