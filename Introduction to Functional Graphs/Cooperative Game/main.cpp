#include <iostream>
#include <string>
#include <vector>
using namespace std;

void move(const vector<int> &to_move) {
    cout << "next";
    for (int i : to_move) {
        cout << ' ' << i;
    }
    cout << endl;
}

vector<int> get_groups() {
    int num_groups; cin >> num_groups;
    vector<int> group_of(10);

    for (int i = 0; i < num_groups; i++) {
        string group; cin >> group;
        for (char piece : group) {
            group_of[piece - '0'] = i;
        }
    }

    return group_of;
}

void discard() {
    get_groups();
}

int main() {
    vector<int> groups;
    do {
        move({0, 1}); discard();
        move({1}); groups = get_groups();
    } while (groups[0] != groups[1]);

    while (groups[2] != groups[1]) {
        move({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        groups = get_groups();
    }

    cout << "done" << endl;
}