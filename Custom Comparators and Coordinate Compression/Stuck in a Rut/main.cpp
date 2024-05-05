#include <iostream>
#include <vector>
#include <algorithm>

struct Cow {
    char dir;
    int x, y, i;
};

bool cmp_north(Cow c1, Cow c2) {
    return c1.x < c2.x;
}

bool cmp_east(Cow c1, Cow c2) {
    return c1.y < c2.y;
}


int main() {
    // try figuring out the range of the rut that a cow leaves and using that
    int n; std::cin >> n;
    std::vector<Cow> northward = {}, eastward = {};

    for (int i = 0; i < n; i++) {
        Cow temp{};
        std::cin >> temp.dir >> temp.x >> temp.y; temp.i = i;

        if (temp.dir == 'N') {
            northward.push_back(temp);
        } else {
            eastward.push_back(temp);
        }
    }

    std::sort(northward.begin(), northward.end(), cmp_north);
    std::sort(eastward.begin(), eastward.end(), cmp_east);

    std::vector<int> blame(n, 0);
    std::vector<bool> stopped(n, false);

    for (Cow east : eastward) {
        for (Cow north : northward) {
            if (!stopped[east.i] && !stopped[north.i] && !(north.x < east.x || east.y < north.y)) {
                if (north.x - east.x > east.y - north.y) {
                    stopped[east.i] = true;
                    blame[north.i] += 1 + blame[east.i];
                } else if (east.y - north.y > north.x - east.x) {
                    stopped[north.i] = true;
                    blame[east.i] += 1 + blame[north.i];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << blame[i] << '\n';
    }
}
