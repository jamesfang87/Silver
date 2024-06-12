#include <iostream>
using namespace std;

// cows will be in the shape of a diamond
int farm[2001][2001];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
int cur_ans = 0;

void add_cows(int x, int y);

bool is_comfortable(int x, int y) {
    int num_neighbors = 0;
    for (int i = 0; i < 4; i++) {
        num_neighbors += (bool) farm[x + dx[i]][y + dy[i]];
    }
    return num_neighbors == 3;
}

void make_uncomfy(int x, int y) {
    // make the current cow uncomfy
    if (is_comfortable(x, y)) {
        add_cows(x, y);
    }

    // check to see if the addition of this cow made its neighbors uncomfy
    for (int i = 0; i < 4; i++) {
        if (is_comfortable(x + dx[i], y + dy[i]) && farm[x + dx[i]][y + dy[i]] != 0) {
            add_cows(x + dx[i], y + dy[i]);
        }
    }
}

void add_cows(int x, int y) {
    for (int i = 0; i < 4; i++) {
        if (farm[x + dx[i]][y + dy[i]] == 0) {
            // update ans and fill in the gap
            cur_ans++;
            farm[x + dx[i]][y + dy[i]] = 2;

            // check to see if the cow we've placed is uncomfy or has made any neighbors uncomfy
            make_uncomfy(x + dx[i], y + dy[i]);
            break;  // since there is only one gap when a cow is uncomfy
        }
    }
}

int main() {
    /*
     * because of the way that being comfy is defined and the fact that we have to make all cows uncomfy,
     * farmer nhoj is forced to place cows in the free space whenever a cow is comfy
     *
     * thus, when farmer nhoj places a cow, we make the cow he placed uncomfy (if it's comfy)
     * and do the same for all its surrounding cows
     *
     * whenever, we place a cow, we also do the same thing
     */
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x += 500; y += 500;

        // notice that after adding cows to make the current configuration of cows all uncomfy
        // when farmer nhoj adds a new cow, we will still need to place essentially the same cows
        // the only scenario where we have to change the cows we placed before would be when farmer nhoj
        // places a cow in a place where we have previously placed one in the last configuration
        // we can just subtract one to account fo this
        if (farm[x][y] == 2) {
            cur_ans--;
        }
        farm[x][y] = 1;

        make_uncomfy(x, y);
        cout << cur_ans << endl;
    }
}
