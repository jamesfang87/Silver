#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("highcard.in");
    ofstream fout("highcard.out");

    int n; fin >> n;
    set<int> bessie_cards, elise_cards;
    int order[n];
    for (int i = 0; i < n; i++) {
        int c; fin >> c;
        elise_cards.insert(c);
        order[i] = c;
    }

    for (int i = 0; i < n * 2; i++) {
        if (elise_cards.count(i + 1) == 0)
            bessie_cards.insert(i + 1);
    }

    int ans = 0;
    for (int card : order) {
        auto optimal_card = bessie_cards.lower_bound(card);
        if (optimal_card != bessie_cards.end()) {
            ans++;
            bessie_cards.erase(optimal_card);
        }
    }
    fout << ans;
}
