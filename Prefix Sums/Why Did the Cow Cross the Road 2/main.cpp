#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("maxcross.in");
    ofstream fout("maxcross.out");

    int n, k, b; fin >> n >> k >> b;

    int num_broken[n + 1]; num_broken[0] = 0;
    int not_working[b];

    for (int& i : not_working) {
        fin >> i;
    }

    sort(not_working, not_working + b);


    int j = 0;
    for (int i = 1; i <= n; i++) {
        if (i == not_working[j]) {
            num_broken[i] = num_broken[i - 1] + 1;
            j++;
        } else {
            num_broken[i] = num_broken[i - 1];
        }
    }


    int answer = INT32_MAX;
    for (int i = 0; i <= n - k; i++) {
        answer = min(answer, num_broken[i + k] - num_broken[i]);
    }
    fout << answer;
}