#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream in("haybales.in");
    ofstream out("haybales.out");

    int n, q; in >> n >> q;

    vector<int> haybale_locations(n);
    for (int i = 0; i < n; i++) {
        in >> haybale_locations[i];
    }
    sort(haybale_locations.begin(), haybale_locations.end());

    for (int i = 0; i < q; i++) {
        int start, end; in >> start >> end;

        out << upper_bound(haybale_locations.begin(), haybale_locations.end(), end) -
                lower_bound(haybale_locations.begin(), haybale_locations.end(), start) << '\n';
    }
}
