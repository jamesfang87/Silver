#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("bcount.in");
    ofstream fout("bcount.out");

    int n, q; fin >> n >> q;
    int sequence[n], sum1[n + 1], sum2[n + 1], sum3[n + 1];
    sum1[0] = 0, sum2[0] = 0, sum3[0] = 0;

    int last_1_value = 0, last_2_value = 0, last_3_value = 0;
    for (int i = 0; i < n; i++) {
        fin >> sequence[i];
        if (sequence[i] == 1) {
            sum1[i + 1] = 1 + sum1[i];
            last_1_value = sum1[i + 1];
            sum2[i + 1] = last_2_value;
            sum3[i + 1] = last_3_value;
        }
        else if (sequence[i] == 2) {
            sum2[i + 1] = 1 + sum2[i];
            last_2_value = sum2[i + 1];
            sum1[i + 1] = last_1_value;
            sum3[i + 1] = last_3_value;
        }
        else {
            sum3[i + 1] = 1 + sum3[i];
            last_3_value = sum3[i + 1];
            sum1[i + 1] = last_1_value;
            sum2[i + 1] = last_2_value;
        }
    }


    for (int i = 0; i < q; i++) {
        int lower, upper; fin >> lower >> upper;
        fout << sum1[upper] - sum1[lower - 1] << ' ';
        fout << sum2[upper] - sum2[lower - 1] << ' ';
        fout << sum3[upper] - sum3[lower - 1] << '\n';
    }



}
