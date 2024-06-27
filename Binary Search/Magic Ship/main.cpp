#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int n; 
string wind_directions;

struct Pos {
    long long x, y;
    
    Pos(long long init_x, long long init_y) {
        x = init_x, y = init_y;
    }
    
    Pos() {
        x = 0LL, y = 0LL;
    }
    
    Pos operator + (const Pos& other) const {
        return {x + other.x, y + other.y};
    }
    
    pair<int, int> operator - (const Pos& other) const {
        return make_pair(x - other.x, y - other.y);
    }
    
    Pos operator * (long long scalar) const {
        return {x * scalar, y * scalar};
    }
    
    long long manhattan_dist(const Pos& other) const {
        return abs(other.x - x) + abs(other.y - y);
    }
    
    friend istream &operator>>(istream &in, Pos &p) {
		in >> p.x >> p.y;
		return in;
	}
	
	friend ostream &operator<<(ostream &out, Pos &p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
};

Pos wind(long long day, vector<Pos> pos_prefix) {
    long long num_cycles = day / n, leftover_days = day % n;
    return pos_prefix[n] * num_cycles + pos_prefix[leftover_days];
}

int main() {
    Pos start, goal;
    
    cin >> start >> goal;
    cin >> n >> wind_directions;
    
    // we will need to know the location that the ship is at after n days in the wind
    // because we can easily determine the number of cycles and days leftover
    // thus, we can use prefix sums to determine this

    // maps UDLR to dx, dy
    map<char, Pos> to_num; 
    to_num['U'] = Pos(0, 1);
    to_num['D'] = Pos(0, -1);
    to_num['L'] = Pos(-1, 0);
    to_num['R'] = Pos(1, 0);
    
    // prefix sums array
    vector<Pos> end_positions(n + 1);
    for (int i = 1; i <= n; i++) {
        end_positions[i] = to_num[wind_directions[i - 1]] + end_positions[i - 1];
    }

    long long min_days = 0, max_days = 1e18;
    while (min_days < max_days) {
        long long test = min_days + (max_days - min_days) / 2;
        Pos cur_pos = start + wind(test, end_positions);

        // the wind 
        
        if (cur_pos.manhattan_dist(goal) <= test) {
            max_days = test;
        } else {
            min_days = test + 1;
        }
    }
    
    if (min_days == 1000000000000000000) {
        cout << -1;
    } else {
        cout << min_days;
    }
}