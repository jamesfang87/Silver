#include <iostream>
#include <set>
using namespace std;

int main() {
    int n; cin >> n;
    int cards[n];
    for (int& c : cards) {
        cin >> c;
    }

    multiset<int> william_choices = {max(cards[0], cards[1])};
    for (int i = 2; i < n; i += 2) {
        int worst_choice = *william_choices.begin();

        if (min(cards[i], cards[i + 1]) > worst_choice) {
            william_choices.erase(william_choices.begin());
            william_choices.insert(cards[i]);
            william_choices.insert(cards[i + 1]);
        } else {
            william_choices.insert(max(cards[i], cards[i + 1]));
        }
    }

    long long ans = 0;
    for (int choice : william_choices) {
        ans += choice;
    }
    cout << ans;
}