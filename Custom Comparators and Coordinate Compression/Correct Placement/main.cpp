#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

struct Friend {
    int h, w, original_index;
};

bool cmp_h(const Friend &x, const Friend &y) { 
    if (x.h == y.h) return x.w > y.w;
    return x.h > y.h;
}

int search(Friend f, vector<Friend> friends, vector<Friend> suffix_min) {
    auto it = upper_bound(all(friends), f, [](const Friend &x, const Friend &y) { return x.h > y.h; });
    if (it != friends.end()) {
        int index = it - friends.begin();
        if (suffix_min[index].w < f.w) {
            return suffix_min[index].original_index + 1;
        }
    }
    return -1;
}

void solve() {
    /*
    sort the friends by their height (or width)
    we can use binary search to quickly segment the friends 
    into ones that can stand in front of the current friend and ones that cannot
    now we need to quickly find a friend with a width that is small enough

    */
    int n; cin >> n;
    vector<Friend> friends_original(n);
    for (int i = 0; i < n; i++) {
        cin >> friends_original[i].h >> friends_original[i].w;
        friends_original[i].original_index = i;
    }

    vector<Friend> friends = friends_original;
    sort(all(friends), cmp_h);

    vector<Friend> suffix_min = friends;
    for (int i = n - 2 ; i >= 0; i--) {
        if (suffix_min[i + 1].w < suffix_min[i].w) {
            suffix_min[i] = suffix_min[i + 1];
        }
    }

    for (auto f : friends_original) {
        int result = search(f, friends, suffix_min);
        if (result != -1) {
            cout << result << ' ';
            goto cont;
        }

        swap(f.h, f.w);
        result = search(f, friends, suffix_min);
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