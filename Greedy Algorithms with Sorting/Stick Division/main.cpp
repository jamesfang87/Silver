#include <iostream>
#include <queue>
using namespace std;

int main() {
    int x, n;
    cin >> x >> n;
    priority_queue<int, vector<int>, greater<>> pq;

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        pq.push(a);
    }

    long long ans = 0;
    for (int i = 1; i < n; i++) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();

        pq.push(a + b);
        ans += a + b;
    }

    cout << ans << "\n";
}