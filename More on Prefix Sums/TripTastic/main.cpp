#include <iostream>
#include <vector>

long long solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<long long>> hotel (n + 1, std::vector<long long> (m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> hotel[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            hotel[i][j] += hotel[i - 1][j] +
                            hotel[i][j - 1] -
                            hotel[i - 1][j - 1];
        }
    }

    if (hotel[n][m] < (k + 1)) {
        return -1;
    }

    // we can use binary search to find the distance between the mentor and the farthest student
    // the ans is a distance where the mentor is at the center and the square/rectangle
    // that has a side len of around 2 * d has a total number of k + 1 rooms or more
    // every distance below the ans will not have a total of at least k + 1 rooms
    // every distance greater than the ans will not be the optimal solution
    auto check = [&](int dist) -> bool {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // pretend (i, j) is the center point of a grid with a sum of at least k + 1
                // we pretend to place the mentor at the center, so he's about equidistant to all students
                // make sure the place we choose isn't 0
                if (hotel[i][j] - hotel[i][j-1] - hotel[i - 1][j] + hotel[i - 1][j - 1] != 0) {
                    // bounds of the rectangle/square
                    int top = std::max(1, i - dist);
                    int bot = std::min(n, i + dist);
                    int left = std::max(1, j - dist);
                    int right = std::min(m, j + dist);
                    long long sum = hotel[bot][right] -
                                    hotel[bot][left - 1] -
                                    hotel[top - 1][right] +
                                    hotel[top - 1][left - 1];
                    if (sum >= (k + 1)) {
                        return true;
                    }
                }
            }
        }
        return false;
    };


    int least_dist = 0;
    int greatest_dist = std::max(n, m);
    int ans = greatest_dist;
    while (least_dist <= greatest_dist) {
        int possible_ans = (least_dist + greatest_dist) / 2;

        // test if this distance works
        // if the square/rect has at least k + 1 rooms, there can be two scenarios
        // 1. we've found the optimal solution and any distance less will not work
        // 2. we've landed on a distance that works but is greater than the optimal one
        // therefore, we should save the answer and try to find something smaller
        // if there's nothing smaller than we can return the answer

        if (check(possible_ans)) {
            // save the answer and move the search range for the dist down
            ans = possible_ans;
            greatest_dist = possible_ans - 1;
        } else { // if not enough room
            // move the search range for the dist up
            least_dist = possible_ans + 1;
        }
    }
    return ans;
}

int main() {
    long long num_cases; std::cin >> num_cases;

    while (num_cases--) {
        std::cout << solve() << '\n';
    }
    return 0;
}
