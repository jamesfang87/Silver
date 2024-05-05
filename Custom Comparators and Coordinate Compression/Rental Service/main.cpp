#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

int main() {
    std::ifstream in("rental.in");
    std::ofstream out("rental.out");
    int n, m, r; in >> n >> m >> r;

    // calculate the maximum amount if FJ milks i cows and rents out n - i cows

    std::vector<int> cows(n, 0);
    std::vector<std::vector<int>> milk_buyers(m);
    std::vector<long long> rent_profits(std::max(n, r) + 1, 0);

    for (int i = 0; i < n; i++) {
        in >> cows[i];
    }

    for (int i = 0; i < m; i++) {
        int gallons, rate; in >> gallons >> rate;
        milk_buyers[i] = {rate, gallons};
    }

    for (int i = 1; i <= r; i++) {
        in >> rent_profits[i];
    }

    std::sort(cows.rbegin(), cows.rend());
    std::sort(milk_buyers.rbegin(), milk_buyers.rend());
    std::partial_sort(rent_profits.begin() + 1,
                      rent_profits.end(),
                      rent_profits.end(),
                      std::greater<>());
    
    std::vector<long long> milk_profits(n + 1, 0);
            
    int last_buyer_id = 0;
    for (int i = 1; i <= n; i++) {
        int addition = cows[i - 1];
        int new_profit = 0;

        if (milk_buyers[m - 1][1] != 0) {
            for (int j = last_buyer_id; j < m; j++) {
                if (addition == 0) {
                    last_buyer_id = j - 1;
                    break;
                }

                new_profit += milk_buyers[j][0] * std::min(addition, milk_buyers[j][1]);
                if (milk_buyers[j][1] >= addition) {
                    milk_buyers[j][1] -= addition;
                    addition = 0;
                } else {
                    addition -= milk_buyers[j][1];
                    milk_buyers[j][1] = 0;
                }
            }
        }
        milk_profits[i] = milk_profits[i - 1] + new_profit;
    }

    for (int i = 1; i <= n; i++) {
        rent_profits[i] += rent_profits[i - 1];
    }


    long long max_profit = 0;
    for (int i = 0; i <= n; i++) {
        max_profit = std::max(milk_profits[i] + rent_profits[n - i], max_profit);
    }
    out << max_profit;
}
