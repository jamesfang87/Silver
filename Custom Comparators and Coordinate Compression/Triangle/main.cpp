#include <bits/stdc++.h>
using namespace std;
typedef long long i64;


struct Point {
    int x, y;
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
    for (auto& f : fence_posts) {
        fin >> f.x >> f.y;
    }

    i64 base_sums[n], height_sums[n];
    memset(base_sums, 0, sizeof base_sums);
    memset(height_sums, 0, sizeof height_sums);

    sort(fence_posts, fence_posts + n, x_comp);
    int i = 0;
    while (i < n) {
        // find sum of heights of all triangles
        // on x = fence_posts[i].x
        int stop = n;
        for (int j = i; j < n; j++) {
            if (fence_posts[j].x != fence_posts[i].x) {
                stop = j;
                break;
            }

            height_sums[i] += fence_posts[j].y - fence_posts[i].y;
        }


        int size = stop - (i + 1);
        for (int j = i + 1; j < stop; j++) {
            height_sums[j] = height_sums[j - 1] + (2 * j - size) * (fence_posts[j].y - fence_posts[j - 1].y);
        }
        i = stop;
    }
    int max_x = fence_posts[n - 1].x;

    sort(fence_posts, fence_posts + n, y_comp);
    for (int i = 0; i < n; i++) {
        fence_posts[i].y = i;
    }
    int max_y = fence_posts[n - 1].y;

    
    

    

}
