#include <iostream>
#include <queue>
using namespace std;

int n;
int num_people[200000], travel_limits[200000];

bool possible(int limit) {
    
}

int main() {
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> num_people[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> travel_limits[i];
    }
    
    int l = 0, r = 1e9 + 1;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (possible(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l;
}