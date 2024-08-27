#include <fstream>
#include <algorithm>
using namespace std;

typedef long long i64;

constexpr int MOD = 1e9 + 7;

struct Point {
    int x, y, original_i;
};

bool x_comp(const Point& a, const Point& b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool y_comp(const Point& a, const Point& b) {
    if (a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

int main() {
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");
    int n; fin >> n;
    Point fence_posts[n];
    for (int i = 0; i < n; i++) {
        fin >> fence_posts[i].x >> fence_posts[i].y;
        fence_posts[i].original_i = i;
    }

    i64 base_sums[n], height_sums[n];

    sort(fence_posts, fence_posts + n, x_comp);
    int i = 0;
    while (i < n) {
        // find sum of heights of all triangles
        // on x = fence_posts[i].x
        int stop = n; // the first index where fence_posts[stop].x != fence_posts[i].x
        int orig_i = fence_posts[i].original_i; // the original index before sorting
        height_sums[orig_i] = 0;
        for (int j = i; j < n; j++) {
            if (fence_posts[j].x != fence_posts[i].x) {
                stop = j;
                break;
            }

            height_sums[orig_i] += fence_posts[j].y - fence_posts[i].y;
        }

        int size = stop - i; // the number of fence posts with the same x coordinate
        int last_index = orig_i; // the original index of fence_posts[j - 1]
        for (int j = i + 1; j < stop; j++) {
            orig_i = fence_posts[j].original_i;
            height_sums[orig_i] = height_sums[last_index] +
                                 (2 * (j - i) - size) *
                                 (fence_posts[j].y - fence_posts[j - 1].y);
            last_index = orig_i;
        }
        i = stop;
    }

    // essentially the same process but flipped for x and y coordinates
    sort(fence_posts, fence_posts + n, y_comp);
    i = 0;
    while (i < n) {
        int stop = n;
        int orig_i = fence_posts[i].original_i;
        base_sums[orig_i] = 0;
        for (int j = i; j < n; j++) {
            if (fence_posts[j].y != fence_posts[i].y) {
                stop = j;
                break;
            }

            base_sums[orig_i] += fence_posts[j].x - fence_posts[i].x;
        }

        int size = stop - i;
        int last_index = orig_i;
        for (int j = i + 1; j < stop; j++) {
            orig_i = fence_posts[j].original_i;
            base_sums[orig_i] = base_sums[last_index] +
                               (2 * (j - i) - size) *
                               (fence_posts[j].x - fence_posts[j - 1].x);
            last_index = orig_i;
        }
        i = stop;
    }

    long long ans = 0;
    for (int j = 0; j < n; j++) {
        ans += base_sums[j] * height_sums[j] % MOD;
        ans %= MOD;
    }
    fout << ans;
}
