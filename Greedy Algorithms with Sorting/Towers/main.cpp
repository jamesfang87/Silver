#include <iostream>
#include <set>
using namespace std;

int main() {
    int n; cin >> n;
    multiset<int> t;

    for (int i = 0; i < n; i++) {
        int s; cin >> s;

        if (t.empty()) {
            t.insert(s);
        } else {
            // find
            auto x = t.upper_bound(s);
            if (x != t.end()) {
                t.erase(x);
            }
            t.insert(s);
        }
    }
    cout << t.size();
}
