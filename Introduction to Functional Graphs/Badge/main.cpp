#include <iostream>
#include <vector>
using namespace std;

vector<int> adj;
vector<int> ans;

int succ(int node) {
    return adj[node];
}

void floyd(int start) {
    // find the start of the loop
    int a = succ(start);
    int b = succ(succ(start));
    while (a != b) {
        a = succ(a);
        b = succ(succ(b));
    }

    a = start;
    while (a != b) {
        a = succ(a);
        b = succ(b);
    }
    int first = a;

    // get answers for the students in the loop
    // (except the start because we do that later for some reason)
    // if a student is in a loop, then they will be visited twice if the teacher starts at it
    b = succ(a);
    ans[b] = b;
    while (a != b) {
        b = succ(b);
        ans[b] = b;
    }

    // get answers for all the other students that are not in a loop
    // and the one at the start of the loop
    // if a student is not in a loop, then they will never be visited twice
    // the student at the start of the loop will
    a = start;
    while (a != succ(first)) {
        ans[a] = first;
        a = succ(a);
    }
    // the loop ends at succ(first) since it is not accounted for in the first loop
}

int main() {
    int n; cin >> n;
    adj = vector<int>(n);
    for (int& temp : adj) {
        cin >> temp;
        temp--;
    }

    // if a student is not in a loop, then they will never be visited twice
    // if a student is in a loop, then they will be visited twice if the teacher starts at it
    ans = vector<int>(n, -1);
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1)
            continue;

        floyd(i);
    }

    for (int a : ans) {
        cout << a + 1 << ' ';
    }
}
