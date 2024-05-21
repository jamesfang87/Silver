#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

long long ans = 0;
int mod = 1e9 + 7;

long long power(long long a, int x) {
    long long ret = 1;
    while (x) {
        if (x % 2) {
            ret *= a;
            ret %= mod;
        }

        a *= a;
        a %= mod;
        x /= 2;
    }
    return ret;
}

void reduce(vector<int>& original) {
    int smallest = original[0];
    for (int& a : original) {
        a -= smallest;
    }

    ans += (int) ((long long) smallest * power(2, original.size() - 1) % mod);
    if (ans >= mod) {
        ans -= mod;
    }
}

vector<int> F(vector<int>& original) {
    reduce(original);
    vector<int> summed(original.size() - 1);

    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < original.size(); i++) {
        for (int j = i + 1; j < original.size(); j++) {
            if (i * j >= original.size())
                break;

            pq.push(original[i] + original[j]);
        }
    }

    for (int& a : summed) {
        a = pq.top(); pq.pop();
    }

    return summed;
}

int main() {
    int n; cin >> n;
    vector<int> array(n);
    for (int& a : array) {
        cin >> a;
    }
    sort(array.begin(), array.end());
    for (int i = 0; i < n - 1; i++) {
        array = F(array);
    }

    cout << (array[0] + ans) % mod;
}
