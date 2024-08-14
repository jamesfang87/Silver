#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

struct Friend {
    int h, w, id;
};

bool operator<(const Friend& lhs, const Friend& rhs) {
    return std::tie(lhs.h, lhs.w, lhs.id) < std::tie(rhs.h, rhs.w, rhs.id);
}

int search(Friend& f, const vector<Friend>& friends, const vector<pair<Friend, Friend>>& prefix_mins) {
    int l = -1, r = friends.size() - 1;
    while (l < r) {
        int m = l + (r - l + 1) / 2;
        if (friends[m].h < f.h) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    
    if (l == -1) {
        return -1;
    }
 
    auto [smallest, sec_smallest] = prefix_mins[l + 1];
    if (smallest.id != f.id) {
        return smallest.w < f.w ? smallest.id : -1;
    } else {
        return sec_smallest.w < f.w ? sec_smallest.id : -1;
    }
}

void solve() {
    int n; cin >> n;
    vector<Friend> unsorted_friends(n);
    for (int i = 0; i < n; i++) {
        cin >> unsorted_friends[i].h >> unsorted_friends[i].w;
        unsorted_friends[i].id = i + 1;
    }

    vector<Friend> friends = unsorted_friends;
    sort(friends.begin(), friends.end());

    vector<pair<Friend, Friend>> prefix_mins = {
        {   
            {INT_MAX, INT_MAX, -1}, 
            {INT_MAX, INT_MAX, -1}
        }
    };
    for (int i = 0; i < n; i++) {
        auto [smallest, sec_smallest] = prefix_mins[i];
        if (friends[i].w < smallest.w) {
            sec_smallest = smallest;
            smallest = friends[i];
        } else {
            sec_smallest = min(sec_smallest, friends[i]);
        }
        prefix_mins.push_back({smallest, sec_smallest});
    }

    for (auto f : unsorted_friends) {
        int result = search(f, friends, prefix_mins);
        if (result != -1) {
            cout << result << ' ';
            goto cont;
        }

        swap(f.h, f.w);
        result = search(f, friends, prefix_mins);
        if (result != -1) {
            cout << result << ' ';
            goto cont;
        }
        
        cout << "-1 ";
        cont:;
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }    
}