#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long i64;

int n;
vector<int> positions;

int ciel(int val) {
    // the first value greater than or equal to val
    int l = -1, r = n - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (positions[mid] >= val) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return positions[l];
}

int floor(int val) {
    // the last value less that or equal to val
    int l = -1, r = n - 1;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (positions[mid] <= val) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return positions[l];
}
 
bool test_left(int landing_pos, int r) {
    if (landing_pos - positions.front() < r) {
        return true;
    }
    
    int cur_pos = landing_pos;
    int cur_r = r;
    while (cur_pos != positions.front()) {
        int next = ciel(cur_pos - cur_r);
        
        if (next >= cur_pos) {
            return false;
        }
        
        cur_pos = next;
        cur_r -= 2;
    }
    return true;
}

bool test_right(int landing_pos, int r) {
    // check if an explosion at landing_pos can propogate all the way to the right
    
    // trival case where the first explosion reaches the end
    if (positions.back() - landing_pos < r) {
        return true;
    }
    
    int cur_pos = landing_pos;
    int cur_r = r;
    while (cur_pos != positions.back()) {
        int next = floor(cur_pos + cur_r);
        
        if (next <= cur_pos) {
            return false;
        }
        
        cur_pos = next;
        cur_r -= 2;
    }
    return true;
}

int get_landing_pos(int test_power) {
    // returns the largest landing position where it is possible to explode
    // all haybales to the left
    
    int min_pos = positions.front() - 1, max_pos = positions.back();
    while (min_pos < max_pos) {
        i64 pos = min_pos + (max_pos - min_pos + 1) / 2;
        if (test_left(pos, test_power)) {
            min_pos = pos;
        } else {
            max_pos = pos - 1;
        }
    }
    return min_pos;
}

int main() {
    ifstream fin("angry.in");
    freopen("angry.out", "w", stdout);
    
    fin >> n;
    positions = vector<int>(n);
    for (int i = 0; i < n; i++) {
        fin >> positions[i];
        positions[i] *= 2;
    }
    sort(positions.begin(), positions.end());
    
    // binary search on the initial blast radius r
    // for each r, go through the following process
    // 1. find a point where it is possible to explode all haybales to the left/right
    //    it does not really matter which side you choose
    //    this process can be done with binary search, since there is a point
    //    where it no longer becomes possible to explode all haybales to the left/right
    // 2. use this point to figure out whether it is possible to explode all haybales in the opposite
    //    direction. this "function" is used to adjust the bounds on r in our "outer" binary search
    
    int min_power = 1, max_power = 1000000000;
    while (min_power < max_power) {
        i64 power = min_power + (max_power - min_power) / 2;
        // get the landing position and test to adjust bounds of power
        if (test_right(get_landing_pos(power), power)) {
            max_power = power;
        } else {
            min_power = power + 1;
        }
    }
    
    printf("%.1f", (double) min_power / 2);
}