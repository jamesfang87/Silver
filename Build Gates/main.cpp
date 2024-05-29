#include <fstream>
#include <cstring>
using namespace std;

char farm[4003][4003];
bool visited[4003][4003] = {false};
int max_r = 2001, min_r = 2001, max_c = 2001, min_c = 2001;

void floodfill(int r, int c) {
    if ((r < min_r || r > max_r || c < min_c || c > max_c)  // if out of bounds
        || farm[r][c] != '.'                // wrong color
        || visited[r][c])  // already visited this square
        return;

    visited[r][c] = true;  // mark current square as visited

    // recursively call flood fill for neighboring squares
    floodfill(r, c + 1);
    floodfill(r, c - 1);
    floodfill(r - 1, c);
    floodfill(r + 1, c);
}

int main() {
    /*
     * idea:
     * we can essentially reduce this problem to finding the number of rooms in a grid
     *
     * let's suppose that the fences divide the farm into N sections
     * out of these N sections, 1 will be the "outside" and N - 1 will be inside fences
     *
     * like in using floodfill to find the number of rooms in a grid
     * the answer is N - 1
     *
     * however, we have to take care of the fact that:
     * ##
     * ##
     * is a region
     *
     * this is pretty simple, we can just double each step in the directions
     * thus, we have basically dilated the farm by x2
     *
     * in our code, we have a 4003 x 4003 array to represent the farm
     * this is because with 1000 directions, we can go 2000 in each direction
     * plus 1 for the origin and 1 "buffer" so we can have the region outside
     *
     * to save time and memory, we keep track of how far in each direction (N, S, E, W) we go
     * this way, we can limit the amount of floodfill calls we have to perform
     */
    ifstream fin("gates.in");
    ofstream fout("gates.out");

    int n; string steps;
    fin >> n >> steps;

    memset(farm, '.', sizeof farm);
    memset(visited, false, sizeof visited);

    int x = 2001, y = 2001;
    for (char step : steps) {
        for (int i = 0; i < 2; i++) {
            switch (step) {
                case 'N':
                    y++;
                    break;
                case 'S':
                    y--;
                    break;
                case 'E':
                    x++;
                    break;
                case 'W':
                    x--;
                    break;
                default:
                    break;
            }

            farm[x][y] = '#';
        }

        min_r = min(min_r, x);
        max_r = max(max_r, x);
        min_c = min(min_c, y);
        max_c = max(max_c, y);
    }

    // expand our bounds so we have that region outside
    min_r--;
    max_r++;
    min_c--;
    max_c++;

    int regions = 0;
    for (int i = min_r; i <= max_r; i++) {
        for (int j = min_c; j <= max_c; j++) {
            if (visited[i][j])
                continue;

            if (farm[i][j] == '#')
                continue;

            floodfill(i, j);
            regions++;
        }
    }

    fout << regions - 1 << endl;
    return 0;
}