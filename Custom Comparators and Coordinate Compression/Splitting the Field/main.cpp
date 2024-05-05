#include <fstream>
#include <set>
#include <vector>
#include <utility>

using namespace std;

long long solve(int n, vector<pair<long long, long long>>& cows) {
    sort(cows.begin(), cows.end());

    set<pair<long long, long long>> side1, side2;
    for (int i = 0; i < n; i++) {
        side1.insert({cows[i].second, cows[i].first});
    }

    long long min = LLONG_MAX;
    for (int i = 0; i < n - 1; i++) {
        side2.insert({cows[i].second, cows[i].first});
        auto itr = side1.find({cows[i].second, cows[i].first});
        side1.erase(itr);

        if (cows[i].first != cows[i + 1].first) {
            long long side1_area = abs(side1.begin()->first - side1.rbegin()->first) *
                                   abs(cows[i + 1].first - cows[n - 1].first);
            long long side2_area = abs(side2.begin()->first - side2.rbegin()->first) *
                                   abs(cows[0].first - cows[i].first);

            min = std::min(side1_area + side2_area, min);
        }
    }

    return min;
}


int main() {
    ifstream in("split.in");
    ofstream out("split.out");

    int n; in >> n;
    vector<pair<long long, long long>> cows;
    for (int i = 0; i < n; i++) {
        pair<long long, long long> temp;
        in >> temp.first >> temp.second;
        cows.push_back(temp);
    }

    long long ans = LLONG_MAX;

    ans = std::min(ans, solve(n, cows));
    long long min_x = cows[0].first, max_x = cows[n - 1].first;

    for (int i = 0; i < n; i++) {
        std::swap(cows[i].first, cows[i].second);
    }

    ans = std::min(ans, solve(n, cows));
    long long min_y = cows[0].first, max_y = cows[n - 1].first;

    out << (max_x - min_x) * (max_y - min_y) - ans;
}