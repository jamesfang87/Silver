#include <fstream>
using namespace std;

int main() {
    ifstream fin("div7.in");
    ofstream fout("div7.out");

    int n; fin >> n;
    long long sums[n + 1];
    sums[0] = 0;

    for (int i = 0; i < n; i++) {
        int temp; fin >> temp;
        sums[i + 1] = sums[i] + temp;
    }

    for (int i = n; i > 0; i--) {
        for (int j = 0; j <= n - i; j++) {
            if ((sums[j + i] - sums[j]) % 7 == 0) {
                fout << i;
                return 0;
            }
        }
    }
}