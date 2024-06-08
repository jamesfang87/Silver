#include <fstream>
#include <vector>
#include <queue>
using namespace std;

vector<int> cows;
int n, max_time;

bool valid(int k) {
    priority_queue<int, vector<int>, greater<>> pq;
    int cur_time = 0, ptr = 0;
    while (ptr < n) {
        while (pq.size() < k) {
            int end_time = cur_time + cows[ptr++];
            pq.push(end_time);
        }

        cur_time = pq.top();
        pq.pop();
    }

    while (!pq.empty()) {
        cur_time = pq.top();
        pq.pop();
    }

    return cur_time <= max_time;
}

int binary_search(int low, int high) {
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (valid(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    ifstream fin("cowdance.in");
    ofstream fout("cowdance.out");

    fin >> n >> max_time;
    for (int i = 0; i < n; i++) {
        int temp; fin >> temp;
        cows.push_back(temp);
    }

    fout << binary_search(1, n);
}
