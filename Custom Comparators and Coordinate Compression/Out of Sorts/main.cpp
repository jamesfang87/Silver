#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream fin("sort.in");
    ofstream fout("sort.out");

    int n; fin >> n;
    int array[n];
    for (int& a : array) {
        fin >> a;
    }


}
