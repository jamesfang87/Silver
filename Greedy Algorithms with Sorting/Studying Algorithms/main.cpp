#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int times[n];
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    std::sort(times, times + n);

    for (int i = 0; i < n; i++) {
        m -= times[i];
        if (m < 0) {
            std::cout << i;
            return 0;
        }
    }
    std::cout << n;
}
