#include <fstream>
#include <map>
#include <vector>
using namespace std;

int n, m;
const int MAX_N = 101;
bool visited[MAX_N][MAX_N] = {false};
bool lit[MAX_N][MAX_N] = {false};
map<pair<int, int>, vector<pair<int, int>>> switches;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool in_range(int r, int c) {
    return (r >= 1 && r <= n && c >= 1 && c <= n);
}

bool connected(int r, int c) {
    for (int i = 0; i < 4; i++) {
        if (!in_range(r + dx[i], c + dy[i])) {
            continue;
        }

        if (visited[r + dx[i]][c + dy[i]]) {
            return true;
        }
    }
    return false;
}

void floodfill(int r, int c) {
    // can not move to this room if it is:
    // 1. already visited
    // 2. unlit
    // 3. not in range
    if (visited[r][c] || !lit[r][c] || !in_range(r, c)) {
        return;
    }

    if (!connected(r, c) && (r != 1 || c != 1)) {
        return;
    }

    // set as visited
    visited[r][c] = true;

    // turn on switches
    pair<int, int> cur = make_pair(r, c);
    for (auto room : switches[cur]) {
        lit[room.first][room.second] = true;
        floodfill(room.first, room.second);
    }

    // move to neighboring rooms
    for (int i = 0; i < 4; i++) {
        floodfill(r + dx[i], c + dy[i]);
    }
}

int main() {
    ifstream cin("lightson.in");
    ofstream cout("lightson.out");

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        pair<int, int> room1; cin >> room1.first >> room1.second;
        pair<int, int> room2; cin >> room2.first >> room2.second;

        switches[room1].push_back(room2);
    }

    lit[1][1] = true;
    floodfill(1, 1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (lit[i][j]) {
                ans++;
            }
        }
    }
    cout << ans;
}
