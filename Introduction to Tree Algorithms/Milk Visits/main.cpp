#include <bits/stdc++.h>
using namespace std;

string cow_species;
vector<vector<int>> adj;
vector<int> component_of;

void dfs(int cur, int prev, int component) {
    component_of[cur] = component;

    for (int neighbor : adj[cur]) {
        if (neighbor != prev && cow_species[neighbor] == cow_species[cur]) {
            dfs(neighbor, cur, component);
        }
    }
}

int main() {
    /*
    let's define a component as connected group of cows with the same species

    if the two cows in a query are in the same component, 
    then the answer is either 1 or 0, depending on the species of cows in the component
    if they are in different components,
    the answer is always yes:

    case 1- the components of the two cows have different breeds:
    either the start or end must have the milk type that the farmer wants

    case 2- the components of the two cows have the same breeds
    if this breed is the same as the breed that the farmer prefers
    then we are done
    otherwise, because of defintion of connected groups, there must at least one cow
    in the path from start to end which is the opposite breed, the one that the farmer prefers
    if there wasn't such cow, then the two cows would be in the same component
    */
    ifstream fin("milkvisits.in");
    ofstream fout("milkvisits.out");
    int n, m;
    fin >> n >> m >> cow_species;

    adj.reserve(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; fin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    component_of.resize(n, -1);
    int cur_component = 0;
    for (int i = 0; i < n; i++) {
        if (component_of[i] == -1) {
            dfs(i, -1, cur_component);
            cur_component++;
        }
    }
    
    for (int i = 0; i < m; i++) {
        int start_point, end_point;
        char milk_preference;
        fin >> start_point >> end_point >> milk_preference;

        if (component_of[start_point - 1] == component_of[end_point - 1]) {
            fout << (cow_species[start_point - 1] == milk_preference);
        } else {
            fout << '1';
        }
    }
}