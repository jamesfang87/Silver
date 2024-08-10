#include <fstream>
#include <sys/wait.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

int n;
string bessie, elsie;
unordered_map<string, string> mother;
unordered_map<string, vector<string> > adj;

string output(string relationship, string younger, string older, int dist) {
    // relationship is either mother or aunt
    string ret = older + " is the ";
    for (int i = 0; i < dist - 1; i++) {
        if (i == dist - 2 && relationship == "mother") ret += "grand-";
        else ret += "great-";
    }
    
    return (ret + relationship + " of " + younger + '\n');
}

bool related(string src, string prev) {
    bool result = (src == elsie);
    for (string neighbor : adj[src]) {
        if (neighbor != prev) {
            result = result || related(neighbor, src);
        }
    }
    return result;
}

int search_direct_ancestors(string younger, string target) {
    // searches direct ancestors for target
    // returns -1 if not found, otherwise the distance between them
    string cur = younger;
    int dist = 0;
    bool found = false;
    while (mother[cur] != "") {
        cur = mother[cur];
        dist++;
        
        if (cur == target) {
            found = true;
            break;
        }
    }
    
    if (found) return dist;
    else return -1;
}

string direct_descendent(string younger, string older) {
    int dist = search_direct_ancestors(younger, older);
    
    if (dist >= 0) return output("mother", younger, older, dist);
    else return "";
}

string aunt(string younger, string older) {
    int dist = search_direct_ancestors(younger, mother[older]);
    
    // subtract one from dist since we are searching for the mother of the aunt
    if (dist >= 0) return output("aunt", younger, older, dist - 1);
    else return "";
}

int main() {
    ifstream fin("family.in");
    ofstream fout("family.out");
    
    fin >> n;
    fin >> bessie >> elsie;
    
    for (int i = 0; i < n; i++) {
        string m, d; 
        fin >> m >> d;
        
        mother[d] = m;
        adj[m].push_back(d);
        adj[d].push_back(m);
    }
    
    if (!related(bessie, "")) {
        fout << "NOT RELATED\n";
        return 0;
    }

    if (mother[bessie] == mother[elsie]) {
        fout << "SIBLINGS\n";
        return 0;
    }
    
    // at least one of these will be ""
    string result = direct_descendent(bessie, elsie) + direct_descendent(elsie, bessie);
    if (!result.empty()) {
        fout << result;
        return 0;
    }
    
    // at least one of these will be ""
    result = aunt(bessie, elsie) + aunt(elsie, bessie);
    if (!result.empty()) {
        fout << result;
        return 0;
    }
    
    fout << "COUSINS\n";
    
    // case 1: siblings
    //  if bessie and elise have the same mother, then they are siblings
    // case 2: direct descendents
    //  since one cow can only have 1 mother, we can travel up the chain, 
    //  starting from one cow and checking if we run into the other.
    //  we first check if bessie is a direct descendent of elsie and then vice versa
    // case 3: aunts
    //  we can check for an aunt by seeing if the mother of an older cow
    //  is a direct ancestor of a younger cow. 
    //  we first check if bessie is an aunt of elsie and then vice versa
    // case 4: cousins
    //  otherwise we output cousins
}