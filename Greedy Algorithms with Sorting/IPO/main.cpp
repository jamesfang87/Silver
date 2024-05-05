#include <algorithm>
#include <utility>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    static int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<pair<int, int>> projects(capital.size());
        for (int i = 0; i < profits.size(); i++) {
            projects[i] = {capital[i], profits[i]};
        }

        sort(projects.begin(), projects.end());
        priority_queue<int> pq;

        int last = 0;
        for (int i = 0; i < k; i++) {
            for (; last < projects.size(); last++) {
                if (projects[last].first > w) {
                    break;
                }

                pq.push(projects[last].second);
            }

            if (!pq.empty()) {
                w +=  pq.top();
                pq.pop();
            }
        }

        return w;
    }
};

int main() {
    int k, w, n; cin >> k >> w >> n;

    vector<int> profits(n);
    for (int i = 0; i < n; i++) {
        cin >> profits[i];
    }

    vector<int> capital(n);
    for (int i = 0; i < n; i++) {
        cin >> capital[i];
    }

    cout << Solution::findMaximizedCapital(k, w, profits, capital);
}