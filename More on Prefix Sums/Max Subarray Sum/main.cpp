#include <iostream>

int main() {
    int n; std::cin >> n;
    int numbers[n];
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }

    int ans = INT_MIN;
    int cur_sum = numbers[0];
    for (int i : numbers) {
        cur_sum = std::max(cur_sum + i, i);
        ans = std::max(ans, cur_sum);
    }
    std::cout << ans;
}