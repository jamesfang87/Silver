#include <iostream>
#include <algorithm>

struct point {
    int x, y;
};

bool cmp_x(point point1, point point2) {
    return (point1.x < point2.x);
}

bool cmp_y(point point1, point point2) {
    return (point1.y < point2.y);
}

int main() {
    int num_points; std::cin >> num_points;

    point points[num_points];
    for (int i = 0; i < num_points; i++) {
        std::cin >> points[i].x >> points[i].y;
    }

    std::sort(points, points + num_points, cmp_x);
    for (int i = 0; i < num_points; i++) {
        points[i].x = i + 1;
    }

    std::sort(points, points + num_points, cmp_y);
    for (int i = 0; i < num_points; i++) {
        points[i].y = i + 1;
    }

    int prefix_points[num_points + 1][num_points + 1];

    // initialize all cells in array to 0
    for (int i = 0; i <= num_points; i++) {
        for (int j = 0; j <= num_points; j++) {
            prefix_points[i][j] = 0;
        }
    }

    // set a cell in the array equal to 1 when there's a cow standing there
    for (int i = 0; i < num_points; i++) {
        prefix_points[points[i].x][points[i].y] = 1;
    }

    // represent the points with prefix sums
    // this way we can quickly count the number of points in a certain area
    for (int i = 1; i <= num_points; i++) {
        for (int j = 1; j <= num_points; j++) {
            prefix_points[i][j] += prefix_points[i - 1][j] + prefix_points[i][j - 1] - prefix_points[i - 1][j - 1];
        }
    }

    long long ans = 1;
    for (int top = 0; top < num_points; top++) {
        for (int bot = top; bot < num_points; bot++) {
            int left = std::min(points[top].x, points[bot].x) - 1;
            int right = std::max(points[top].x, points[bot].x) - 1;

            // we add the number of cows left to the two vertical cows
            // and the number of cows right to them multiplied together
            // that gives us the number of different rectangles we can create
            // * these cows have to their y coordinate between top and bot cows

            int l_num = prefix_points[left + 1][bot + 1] -
                        prefix_points[left + 1][top] -
                        prefix_points[0][bot + 1] +
                        prefix_points[0][top];

            int r_num = prefix_points[num_points][bot + 1] -
                        prefix_points[num_points][top] -
                        prefix_points[right][bot + 1] +
                        prefix_points[right][top];

            ans += l_num * r_num;
        }
    }

    std::cout << ans;
}