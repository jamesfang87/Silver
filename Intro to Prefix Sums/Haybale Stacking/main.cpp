#include <fstream>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin("stacking.in");
    ofstream fout("stacking.out");

    int num_stacks, num_instructions;
    fin >> num_stacks >> num_instructions;

    int stacks[num_stacks];
    int change_of_haybale_nums[num_stacks + 1];

    for (int i = 0; i < num_instructions; i++) {
        int start, end; fin >> start >> end;
        change_of_haybale_nums[start - 1]++;
        change_of_haybale_nums[end]--;
    }

    int sum = 0;
    for (int i = 0; i < num_stacks; i++) {
        sum += change_of_haybale_nums[i];
        stacks[i] = sum;
    }

    sort(stacks, stacks + num_stacks);

    fout << stacks[num_stacks / 2];
}