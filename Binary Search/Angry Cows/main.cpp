#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool possible(long long radius, const vector<long long>& positions, long long k) {
    auto it = positions.begin();
    for (long long i = 0; i < k; i++) {
        long long explosion_end = *it + radius * 2;
        it = upper_bound(positions.begin(), positions.end(), explosion_end);

        if (it == positions.end()) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("angry.in");
    ofstream fout("angry.out");

    long long n, k; fin >> n >> k;

    vector<long long> positions(n);
    for (long long& pos : positions) {
        fin >> pos;
    }
    sort(positions.begin(), positions.end());


    long long low = 1, high = positions[n - 1] + 1;
    while (low < high) {
        long long mid = low + (high - low) / 2;

        if (possible(mid, positions, k)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    fout << low;

}
