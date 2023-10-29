#include <fstream>
int barn[1001][1001];

int main() {
    std::ifstream fin("paintbarn.in");
    std::ofstream fout("paintbarn.out");
    int n, k; fin >> n >> k;

    for (auto & i : barn) {
        for (int & j : i) {
            j = 0;
        }
    }

    while (n--) {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        barn[x1][y1]++;
        barn[x1][y2]--;
        barn[x2][y1]--;
        barn[x2][y2]++;
    }

    int answer = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (i) barn[i][j] += barn[i - 1][j];
            if (j) barn[i][j] += barn[i][j - 1];
            if (i && j) barn[i][j] -= barn[i - 1][j - 1];
            if (barn[i][j] == k) answer++;
        }
    }

    fout << answer;
}