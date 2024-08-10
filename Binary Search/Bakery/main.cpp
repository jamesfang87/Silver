#include <bits/stdc++.h>
using namespace std;

long long n, original_cookie_cost, original_muffin_cost;
vector<long long> cookie_orders, muffin_orders, wait_times;

bool check(long long moonies_spent) {
    // the upper bound on the cost (maxmium time) to bake one cookie and muffin
    long long cookie_cost = original_cookie_cost, muffin_cost = original_muffin_cost;
        
    long long t = original_cookie_cost + original_muffin_cost - moonies_spent; // cached since it appears a lot
    for (long long i = 0; i < n; i++) {
        long long cookies = cookie_orders[i], muffins = muffin_orders[i], wait_time = wait_times[i];
            
        if (cookies > muffins) {
            cookie_cost = min(cookie_cost, (wait_time - muffins * t) / (cookies - muffins));
        } else if (muffins > cookies) {
            muffin_cost = min(muffin_cost, (wait_time - cookies * t) / (muffins - cookies));
        } else {
            if (cookies * t > wait_time) {
                return false;
            }
        }
    }
        
    // the time to bake a pastry cannot be negative or zero
    if (cookie_cost <= 0 || muffin_cost <= 0) {
        return false;
    }
        
    // check that we have not spent more than we could
    long long moonies_spent_on_cookies = original_cookie_cost - cookie_cost;
    long long moonies_spent_on_muffins = original_muffin_cost - muffin_cost;
    if (moonies_spent_on_cookies + moonies_spent_on_muffins > moonies_spent) {
        return false;
    }

    return true;
}

void solve() {
   	cin >> n >> original_cookie_cost >> original_muffin_cost;
   	
    cookie_orders.resize(n); muffin_orders.resize(n); wait_times.resize(n);
    for (long long i = 0; i < n; i++) {
        cin >> cookie_orders[i] >> muffin_orders[i] >> wait_times[i];
    }
   	
    long long min_spent = 0, max_spent = original_cookie_cost + original_muffin_cost - 2;
    while (min_spent < max_spent) {
        long long moonies_spent = min_spent + (max_spent - min_spent) / 2;
        if (check(moonies_spent)) {
            max_spent = moonies_spent;
        } else {
            min_spent = moonies_spent + 1;
        }
    }
    cout << min_spent << '\n';
}

int main() {
    long long t; cin >> t;
    while (t--) {
   	    solve();
    }
}
