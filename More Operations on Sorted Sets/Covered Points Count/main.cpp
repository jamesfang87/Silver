#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Range {
    long long start, end;
};

long long compress(long long i, vector<long long>& indices) {
    return lower_bound(indices.begin(), indices.end(), i) - indices.begin();
}

int main() {
    int n; cin >> n;
    vector<long long> indices;
    vector<Range> updates(n);
    for (int i = 0; i < n; i++) {
        long long a, b; cin >> a >> b;
        indices.push_back(a);
        indices.push_back(b + 1);

        updates[i] = {a, b + 1};
    }

    sort(indices.begin(), indices.end());
    indices.erase(std::unique(indices.begin(), indices.end()), indices.end());

    vector<long long> difference_array(indices.size(), 0);
    for (Range update: updates) {
        long long compressed_start = compress(update.start, indices);
        long long compressed_end = compress(update.end, indices);
        difference_array.at(compressed_start)++;
        difference_array.at(compressed_end)--;
    }

    vector<long long> interval_values(indices.size(), 0);
    for (int i = 1; i < interval_values.size(); i++) {
        interval_values.at(i) += interval_values.at(i - 1) + difference_array.at(i - 1);
    }

    vector<long long> ans(n, 0);
    for (int i = 1; i < interval_values.size(); i++) {
        if (interval_values[i] != 0) {
            ans[interval_values[i] - 1] += indices[i] - indices[i - 1];
        }
    }

    for (auto a : ans) {
        cout << a << ' ';
    }
}