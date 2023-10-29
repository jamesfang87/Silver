#include <fstream>

int main() {
    std::ifstream fin("lazy.in");
    std::ofstream fout("lazy.out");

    int n, k; fin >> n >> k;

    int field[n][n];
    for (auto & i : field) {
        for (int & j : i) {
            fin >> j;
        }
    }

    int prefix[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        prefix[0][i] = 0;
        prefix[i][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = field[i - 1][j - 1] + prefix[i][j - 1];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int sum = prefix[i][std::min(n, j + k)] - prefix[i][std::max(0, j - k - 1)];

            for (int a = 1; a <= k; a++) {
                if ((i + a) <= n) {
                    sum += prefix[i + a][std::min(n, j + k - a)] - prefix[i + a][std::max(0, j - k + a - 1)];
                } else {
                    break;
                }
            }

            for (int a = 1; a <= k; a++) {
                if (i - a >= 0) {
                    sum += prefix[i - a][std::min(n, j + k - a)] - prefix[i - a][std::max(0, j - k + a - 1)];
                } else {
                    break;
                }
            }
            ans = std::max(ans, sum);
        }
    }
    fout << ans;
}