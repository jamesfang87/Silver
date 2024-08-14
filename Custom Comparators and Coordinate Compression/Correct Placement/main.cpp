#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <climits>
using namespace std;

#define all(x) x.begin(), x.end()

struct Friend {
    int h, w, index;
};

bool operator<(const Friend& lhs, const Friend& rhs) {
    return std::tie(lhs.h, lhs.w, lhs.index) < std::tie(rhs.h, rhs.w, rhs.index);
}

int search(Friend& f, vector<Friend>& friends, vector<pair<Friend, Friend>>& prefix_mins) {
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

    auto [first_choice, second_choice] = prefix_mins[l + 1];
    if (first_choice.index != f.index) {
        return first_choice.w < f.w ? first_choice.index : -1;
    } else {
        return second_choice.w < f.w ? second_choice.index : -1;
    }
}

void solve() {
    int n; cin >> n;
    vector<Friend> unsorted_friends(n);
    for (int i = 0; i < n; i++) {
        cin >> unsorted_friends[i].h >> unsorted_friends[i].w;
        unsorted_friends[i].index = i + 1;
    }

    vector<Friend> friends = unsorted_friends;
    sort(friends.begin(), friends.end());

    vector<pair<Friend, Friend>> prefix_mins = {{{INT_MAX, INT_MAX, -1}, {INT_MAX, INT_MAX, -1}}};
    for (int i = 0; i < friends.size(); i++) {
        Friend least_w = prefix_mins[i].first, second_least_w = prefix_mins[i].second;

        least_w = friends[i].w <= least_w.w ? friends[i] : least_w;
        second_least_w = friends[i].w < second_least_w.w ? friends[i] : second_least_w;

        prefix_mins.push_back({least_w, second_least_w});
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
        swap(f.h, f.w);
        
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