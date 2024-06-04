#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;

    vector<vector<int>> preferences(n);
    for (int cow = 0; cow < n; cow++) {
        for (int g = 0; g < n; g++) {
            int gift; cin >> gift; gift--;
            preferences[cow].push_back(gift);
        }
        while (preferences[cow].back() != cow) {
            preferences[cow].pop_back();
        }
    }

    // definitions:
    // edge g -> i exists if cow i prefers gift g over gift i

    // valid assignments:
    // the cows that get and receive gifts must be in a cycle
    // if it's in a functional graph then one gift goes nowhere and a cow is missing a gift
    // because of the way that edges work, every cow in the cycle will be better off if they trade

    // for an assignment of gift g to cow i (which cow i prefers) to be valid
    // cow g must get a gift it prefers over gift g
    // this can be in a cycle with more than 2 cows or in an exchange directly between cows i and g
    // in the first case
    // every cow must prefer the gift it receives over the original
    // ex: cow i's gift -> cow j and cow j's gift -> cow g and gift g is received by cow i
    // only possible if every cow must prefer the gift it receives over the original

    // in terms of graphs,
    // the cows must be in a cycle
    // so there must be a path from i to g and g to i
    // every cow must prefer the gift it receives over the original
    // since edges represents preferences of a gift over the one the cow already has

    // answers:
    // we can loop through all the gifts in order of most preferred to the only cow i already has
    // if there is path from i to g, then we can end the search and output an answer for cow i
    // (because of the search order we guarantee that there is edge g -> i or that cow i prefers gift g)

    // to figure out what paths we have, we can use dfs or floyd-marshall

    vector<vector<bool>> is_path(n, vector<bool>(n, false));

    // construct edges
    // edge g -> i exists if cow i prefers gift g over gift i
    for (int cow = 0; cow < n; cow++) {
        for (int gift : preferences[cow]) {
            is_path[gift][cow] = true;
        }
    }

    for (int cow2 = 0; cow2 < n; cow2++) {
        for (int cow1 = 0; cow1 < n; cow1++) {
            for (int cow3 = 0; cow3 < n; cow3++) {
                is_path[cow1][cow3] = is_path[cow1][cow3] || (is_path[cow1][cow2] && is_path[cow2][cow3]);
            }
        }
    }

    for (int cow = 0; cow < n; cow++) {
        for (int gift: preferences[cow]) {
            if (is_path[cow][gift]) {
                cout << gift + 1 << '\n';
                break;
            }
        }
    }
}
