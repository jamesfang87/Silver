#include <iostream>

int main() {
    int n, m; std::cin >> n >> m;

    int trees[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char point; std::cin >> point;
            trees[i][j] = (point == '*');
        }
    }

    int prefix[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        prefix[0][i] = 0;
        prefix[i][0] = 0;
    }


    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = trees[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }

    while (m--) {
        int y1, x1, y2, x2;
        std::cin >> y1 >> x1 >> y2 >> x2;
        std::cout << prefix[y2][x2] - prefix[y1 - 1][x2] - prefix[y2][x1 - 1] + prefix[y1 - 1][x1 - 1] << std::endl;
    }
}