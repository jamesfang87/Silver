#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, capacity; cin >> n >> capacity;
    int children[n];
    for (int& c : children) {
        cin >> c;
    }

    sort(children, children + n);

    int ans = n;

    cout << ans;
}



// 2 3 5 6 7 9
// 27

// 36

// 5

// 9

// 4