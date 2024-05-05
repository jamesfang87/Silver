#include <iostream>
#include <vector>
#include <algorithm>

struct Time {
    int time;
    bool leaving;
};

bool cmp(const Time &x, const Time &y) { return x.time < y.time; }

int main() {
    int n; std::cin >> n;

    std::vector<Time> times (n *  2);
    for (int i = 0; i < n * 2; i += 2) {
        int enter, leave; std::cin >> enter >> leave;
        times[i].time = enter; times[i].leaving = false;
        times[i + 1].time = leave; times[i + 1].leaving = true;
    }
    
    std::sort(times.begin(), times.end(), cmp);

    int maxCustomer = -10000;
    int curNum = 0;
    for (Time i : times) {
        if (i.leaving) {
            curNum--;
        } else if (!i.leaving) {
            curNum++;
        }

        maxCustomer = std::max(curNum, maxCustomer);
    }

    std::cout << maxCustomer;

}
