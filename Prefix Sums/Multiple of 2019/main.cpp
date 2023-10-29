#include <bits/stdc++.h>
using namespace std;

int main() {
    string str; cin >> str;
    unsigned long long num = 0, pow = 1;
    map<int, long long> mod_2019; mod_2019[0] = 1;

    for (int i = str.size() - 1; i >= 0; i--) {
        num = (num + pow * (str[i] - '0')) % 2019;
        mod_2019[num]++;
        pow = pow * 10 % 2019;
    }

    long long ans = 0;
    for (auto i : mod_2019) {
        ans += i.second * (i.second - 1) / 2;
    }
    cout << ans << endl;
    return 0;
}