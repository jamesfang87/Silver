#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;

    // holds ans in the form of lines
    vector<vector<int>> ans;
    
    while (n--) {
        int a; cin >> a;
        int low = 0, high = ans.size();
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (ans[mid].back() < a) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        // if none are smaller than the current element in the array
        if (low == ans.size()) {
            // the current element must be a part of a new sequence
            ans.push_back({a});
        } else {
            // otherwise push it to that sequence
            ans[low].push_back(a);
        }
    }

    for (auto& line : ans) {
        for (int& a : line ) {
            cout << a << ' ';
        }
        cout << '\n';
    }
}
