#include <iostream>
#include <fstream>
#include <vector>


struct Mountain {
    int x, y, l, r;


    bool inside(Mountain other) const {
        return (other.l <= this->x && this->x <= other.r && this->y <= -1 * abs(this->x - other.x) + other.y);
    }
};


int main() {
    std::ifstream in("mountains.in");
    std::ofstream out("mountains.out");

    int n; in >> n;
    std::vector<Mountain> mountains(n);
    for (int i = 0; i < n; i++) {
        in >> mountains[i].x >> mountains[i].y;
        mountains[i].l = -1 * mountains[i].y + mountains[i].x;
        mountains[i].r = mountains[i].y + mountains[i].x;
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i !=j && mountains[i].inside(mountains[j])) {
                count--;
                break;
            }
        }
        count++;
    }
    out << count;
}
