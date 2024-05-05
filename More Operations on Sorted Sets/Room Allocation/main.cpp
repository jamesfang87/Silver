#include <iostream>
#include <utility>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Customer {
    int start, end, original_index;
};

bool cmp(Customer a, Customer b) {
    return a.start < b.start;
}

int main() {
    int n; cin >> n;
    vector<Customer> customers(n);
    for (int i = 0; i < n; i++) {
        cin >> customers[i].start >> customers[i].end;
        customers[i].original_index = i;
    }

    sort(customers.begin(), customers.end(), cmp);

    multiset<pair<int, int>> end_times = {{-1, 1}};
    int num = 1;
    int ans = INT32_MIN;
    vector<int> history(n);
    for (auto c : customers) {
        if (c.start <= end_times.begin()->first) {
            end_times.insert({c.end, ++num});
            history[c.original_index] = num;
        } else {
            auto it = end_times.upper_bound({c.start, -1});
            int code = prev(it)->second;
            end_times.erase(--it);
            end_times.insert({c.end, code});
            history[c.original_index] = code;
        }
        ans = max(ans, (int) end_times.size());
    }

    cout << ans << '\n';
    for (int h : history) {
        cout << h << ' ';
    }
}
