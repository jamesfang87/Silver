#include <iostream>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    long long ans = 0;

    long long min_given[n];
    for (long long& b : min_given) {
        cin >> b;
        ans += b;
    }
    ans *= m;

    long long max_received[m];
    for (long long& g : max_received) {
        cin >> g;
    }

    sort(min_given, min_given + n, greater<>());
    sort(max_received, max_received + m, greater<>());

    if (min_given[0] > max_received[m - 1]) {
        cout << -1;
        return 0;
    }


    // max_received[0] >= every element in min_given
    // for this code to run


    // use the boy who gives the most candy at least to give candy to the girls
    for (int g = 0; g < m - 1; g++) {
        ans += max_received[g] - min_given[0];
    }


    // this boy will still have to give the minimum amount of candy
    // thus, if the least maximum amount a girl received is greater than
    // this minimum amount, use the next boy

    // we know that max_received[m - 1] or anything before is not smaller than min_given[0]
    // but it can be equal to min_given[0]
    // in that case, this conditional fails, and we add 0 (do nothing)
    if (max_received[m - 1] > min_given[0]) {
        ans += max_received[m - 1] - min_given[1];
    }

    cout << ans;
}