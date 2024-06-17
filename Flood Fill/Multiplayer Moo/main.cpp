#include <fstream>
#include <set>
using namespace std;

int n;
const int MAX_N = 250;
int board[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
set<pair<int, int> > called[MAX_N][MAX_N];
int row_change[4] = {0, 0, 1, -1};
int col_change[4] = {1, -1, 0, 0};

bool invalid_pos(int r, int c) {
    return (r < 0 || r >= n || c < 0 || c >= n);
}

// floodfill function for the 1st part of the answer
// only 1 valid color
int floodfill1(int r, int c, int color) {
    if (invalid_pos(r, c) || visited[r][c] || board[r][c] != color) {
        return 0;
    }

    visited[r][c] = true;

    int area_claimed = 1;
    for (int i = 0; i < 4; i++) {
        area_claimed += floodfill1(r + row_change[i], c + col_change[i], color);
    }
    return area_claimed;
}

// floodfill function for the 2nd part of the answer:
// two valid colors
int floodfill2(int r, int c, pair<int, int> valid_colors) {
    if (invalid_pos(r, c) || called[r][c].count(valid_colors) == 1) {
        return 0;
    }

    if (board[r][c] != valid_colors.first && board[r][c] != valid_colors.second) {
        return 0;
    }

    called[r][c].insert(valid_colors);

    int area_claimed = 1;
    for (int i = 0; i < 4; i++) {
        area_claimed += floodfill2(r + row_change[i], c + col_change[i], valid_colors);
    }
    return area_claimed;
}

int main() {
    ifstream fin("multimoo.in");
    ofstream fout("multimoo.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> board[i][j];
        }
    }

    // the first part of our answer is trivial:
    // see code below for details

    int ans1 = 1; // max area that one cow claims
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (!visited[r][c]) {
                ans1 = max(ans1, floodfill1(r, c, board[r][c]));
            }
        }
    }
    fout << ans1 << '\n';

    // in part 2 of our answer,
    // we find the largest region which contains up to 2 different colors
    //
    // a naive solution might be to loop over all possible pairs of colors and find the maximum area
    // this is too slow since there are 10^6 possible colors,
    // which would probably be too slow even if we could find in constant time the largest area for each color pair
    //
    // to optimize, lets examine how we can increase area by choosing an "optimal" 2nd color for a cell
    // to increase area at all, we must choose a color which the current cell borders
    // the color should also not be the same as the color of the cell
    // thus, we have narrowed down the amount of color pairs for a single cell down to at most 4!
    //
    // we can loop through each cell, starting 4 floodfills from each cell with the valid colors being
    // board[r][c] and the color of each neighbor
    // this is fast enough to pass 9/10 test cases using memset to reset the visited 2d array!
    //
    // however, we are doing a lot of extra work: mainly we are revisiting every region multiple times
    // let's take an example; when we visit an arbritary r and c,
    // one of our floodfill calls will have the 2nd valid color be the color of the right neighbor
    // however, the next cell, which is the right neighbor, will result in a call visiting the same region
    // with the same color combination: the color of board[r][c] and board[r][c + 1]
    // there are other cases more complicated than this where
    // we are doing extra work revisiting a region with the same color combination
    //
    // to account for this, let's create a 2d array (the same size of the board) of sets
    // representing the color combinations which have visited each cell
    // thus, when we call our floodfill,
    // if we see that a search with the same color combination has already visited a cell
    // we prune the search

    int ans2 = 0; // max area that a team of two cows claims
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            // note that any calls with an out of range neighbor will be immediately pruned
            // so it's fine to loop through all neighbors even on edge cells
            for (int i = 0; i < 4; i++) {
                int new_r = r + row_change[i];
                int new_c = c + col_change[i];

                // only run floodfill when the color of the neighbor is different
                if (board[r][c] != board[new_r][new_c]) {
                    pair<int, int> valid_colors = make_pair(board[r][c], board[new_r][new_c]);
                    // searching with a color combination (a, b) is the same as searching with (b, a)
                    // we swap so that the pair is sorted to account for this
                    if (valid_colors.first > valid_colors.second) {
                        swap(valid_colors.first, valid_colors.second);
                    }
                    ans2 = max(ans2, floodfill2(r, c, valid_colors));
                }
            }
        }
    }
    fout << ans2 << '\n';
}
