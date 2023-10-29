#include <iostream>
#include <cstring>


struct point {
    int x, y;
};


int main() {
    int n, m, q;
    std::cin >> n >> m >> q;

    int grid[n + 2][m + 2];
    memset(grid, 0, sizeof(grid));
    for (int i = 1; i <= n; i++) {
        std::string temp; std::cin >> temp;
        for (int j = 1; j <= m; j++) {
            grid[i][j] = temp[j - 1] - 48;
        }
    }


    int num_vertices[n + 1][m + 1], horizontal_edges[n + 1][m + 1], vertical_edges[n + 1][m + 1];
    memset(num_vertices, 0, sizeof(num_vertices));
    memset(horizontal_edges, 0, sizeof(horizontal_edges));
    memset(vertical_edges, 0, sizeof(vertical_edges));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            num_vertices[i][j] = grid[i][j] + num_vertices[i - 1][j] +
                    num_vertices[i][j - 1] - num_vertices[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == 1 && grid[i][j - 1] == 1)
                horizontal_edges[i][j] += 1;
            if (grid[i][j] == 1 && grid[i - 1][j] == 1)
                vertical_edges[i][j] += 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            horizontal_edges[i][j] += horizontal_edges[i - 1][j] +
                    horizontal_edges[i][j - 1] - horizontal_edges[i - 1][j - 1];
            vertical_edges[i][j] += vertical_edges[i - 1][j] +
                                      vertical_edges[i][j - 1] - vertical_edges[i - 1][j - 1];
        }
    }


    while (q--) {
        point from = {}, to = {};
        std::cin >> from.x >> from.y >> to.x >> to.y;

        // a tree is a graph with v vertices and v - 1 edges
        // a forest a graph whose components that are connected are trees
        // the number of trees in a forest can be calculated by subtracting
        // the total number of edges from the total number of vertices
        // we can use 2-d prefix sums to store the number of edges and vertices

        // subtract number of edges from the number of vertices between the two points
        // using the prefix arrays from above

        // in some cases, such as in the last 2 queries of the first sample
        // one of the vertices that create an edge lie outside the subarray in the query
        // therefore, the edge should not be counted
        // since an edge between points (i, j) and (i + 1, j) or (i, j + 1) is stored at the latter point
        // we can change our start x or y coordinate by adding one to it
        // this will get rid of all extraneous edges for each "dimension" (x or y)

        int vertices = num_vertices[to.x][to.y] - num_vertices[from.x - 1][to.y] -
                num_vertices[to.x][from.y - 1] + num_vertices[from.x - 1][from.y - 1];
        int num_vertical_edges = vertical_edges[to.x][to.y] - vertical_edges[from.x][to.y] -
                vertical_edges[to.x][from.y - 1] + vertical_edges[from.x][from.y - 1];
        int num_horizontal_edges = horizontal_edges[to.x][to.y] - horizontal_edges[from.x - 1][to.y] -
                horizontal_edges[to.x][from.y] + horizontal_edges[from.x - 1][from.y];
        std::cout << vertices - num_vertical_edges - num_horizontal_edges << '\n';
    }
    return 0;
}
