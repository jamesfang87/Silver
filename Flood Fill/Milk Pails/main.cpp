#include <fstream>
#include <algorithm>
#include <map>
#include <iostream>
#include <utility>
using namespace std;

int pail1_capacity, pail2_capacity, max_depth, m;
map<tuple<int, int, int>, int> visited;

int search(int depth, int pail1, int pail2) {
    if (depth == max_depth) {
        return abs(m - (pail1 + pail2));
    }

    if (visited.count({pail1, pail2, depth}) == 1) {
        return visited[{pail1, pail2, depth}];
    } else {
        visited[{pail1, pail2, depth}] = abs(m - (pail1 + pail2));
    }

    // option 1: fill pail1
    int option1 = search(depth + 1, pail1_capacity, pail2);

    // option 2: fill pail2
    int option2 = search(depth + 1, pail1, pail2_capacity);

    // option 3: empty pail1
    int option3 = search(depth + 1, 0, pail2);

    // option 4: empty pail2
    int option4 = search(depth + 1, pail1, 0);

    // option 5: empty pail1 -> pail2
    int pail_2_free_space = abs(pail2_capacity - pail2);
    int pail1_prime = max(0, pail1 - pail_2_free_space);
    int pail2_prime = min(pail2_capacity, pail2 + pail1 - pail1_prime);

    int option5 = search(depth + 1, pail1_prime, pail2_prime);

    // option 6: empty pail2 -> pail1
    int pail_1_free_space = abs(pail1_capacity - pail1);
    pail2_prime = max(0, pail2 - pail_1_free_space);
    pail1_prime = min(pail1_capacity, pail1 + pail2 - pail2_prime);

    int option6 = search(depth + 1, pail1_prime, pail2_prime);

    int ans = min({option1, option2, option3, option4, option5, option6});
    return ans;
}

int main() {
    ifstream fin("pails.in");
    ofstream fout("pails.out");

    fin >> pail1_capacity >> pail2_capacity;
    fin >> max_depth >> m;

    fout << search(0, 0, 0) << '\n';
}
