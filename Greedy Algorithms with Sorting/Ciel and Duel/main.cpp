#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct card {
    string pos;
    int power{};
};

bool cmp1(const card& a, const card& b) {
    if (a.pos == b.pos) return a.power < b.power;
    return a.pos[0] > b.pos[0];
}

int main() {
    int n, m; cin >> n >> m;

    vector<int> atk, def;
    vector<card> jiro(n);
    for (int i = 0; i < n; i++) {
        string pos; cin >> pos;
        int power; cin >> power;

        if (pos == "ATK")
            atk.push_back(power);
        if (pos == "DEF")
            def.push_back(power);

        jiro[i] = {pos, power};
    }

    vector<int> ciel(m); vector<bool> used(m);
    for (int i = 0; i < m; i++) {
        cin >> ciel[i];
        used[i] = false;
    }

    sort(atk.begin(), atk.end());
    sort(def.begin(), def.end());
    sort(ciel.begin(), ciel.end());

    int damage1 = 0;
    int all_broken = true;

    int ptr = ciel.size() - 1;
    for (int i : atk) {
        if (ptr == -1) break;

        if (ciel[ptr] >= i) {
            damage1 += ciel[ptr] - i;
            used[ptr] = true;
            ptr--;
        } else {
            all_broken = false;
            break;
        }
    }

    // save the higher cards for the end
    if (def.size() > 0) {
        ptr = -1;
        for (int i = 0; i < ciel.size(); i++) {
            if (ciel[i] > def[0]) {
                ptr = i;
                break;
            }
        }

        if (ptr == -1) {
            cout << damage1;
            return 0;
        }
    }


    int num_broken = 0;
    for (int i : def) {
        while ((used[ptr] || ciel[ptr] < i) && (ptr < ciel.size() - 1))
            ptr++;

        if (ciel[ptr] > i && !used[ptr]) {
            num_broken++;
            used[ptr] = true;
        }

        if (ptr == ciel.size() - 1) break;
    }

    if (num_broken < def.size()) {
        all_broken = false;
    }

    if (all_broken) {
        for (int i = 0; i < m; i++) {
            if (!used[i])
                damage1 += ciel[i];
        }
    }

    for (int i = 0; i < m; i++) {
        used[i] = false;
    }

    sort(jiro.begin(), jiro.end(), cmp1);
    for (auto& j : jiro) {
        std::cout << j.power << ' ' << j.pos << endl;
    }

    int damage2 = 0;
    int broken = 0;
    for (int i = 0; i < n; i++) {
        if (jiro[i].pos == "ATK") {
            for (int j = 0; j < m; j++) {
                if (ciel[j] >= jiro[i].power && !used[j]) {
                    used[j] = true;
                    damage2 += ciel[j] - jiro[i].power;
                    broken++;
                    break;
                }
            }
        } else {
            for (int j = 0; j < m; j++) {
                if (ciel[j] > jiro[i].power && !used[j]) {
                    used[j] = true;
                    broken++;
                    break;
                }
            }
        }
    }

    if (broken == jiro.size()) {
        for (int i = 0; i < m; i++) {
            if (!used[i])
                damage2 += ciel[i];
        }
    }

    cout << max(damage1, damage2);
}