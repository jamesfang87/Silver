#include <iostream>
#include <set>
using namespace std;

int main() {
    int n, m; cin >> n >> m;

    multiset<int, greater<>> prices;
    for (int i = 0; i < n; i++) {
        int price; cin >> price;
        prices.insert(price);
    }

    for (int i = 0; i < m; i++) {
        int budget; cin >> budget;

        auto it = prices.lower_bound(budget);
        if (it == prices.end()) {
            cout << -1 << '\n';
        } else {
            cout << *it << '\n';
            prices.erase(it);
        }
    }
}
