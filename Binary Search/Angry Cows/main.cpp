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
    /*
     * binary search on the radius
     *
     * hard part is figuring if a combination of R and K work
     * to maximize the amount of haybales that are exploded,
     * we start at the lowest position and have that be the endpoint of the explosion
     * essentially we aim a cow at pos x = position + R
     *
     * we continue this until we run out of cows, or we blow up the last haybale
     *
     * it's possible to do this in O(n) time with a while loop
     * we can also do this in O(logn) time using std::upper_bound
     * we just have to check with each iteration rather than just lazily at the end
     * since positions.end(), which is returned by std::upper_bound when no elements are greater
     * could be negative meaning std::upper_bound returns positions.begin() the next iteration
     */
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
