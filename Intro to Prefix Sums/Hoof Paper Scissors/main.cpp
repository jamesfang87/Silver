#include <fstream>
using namespace std;

int main() {
    ifstream fin("hps.in");
    ofstream fout("hps.out");

    int n; fin >> n;

    int sumH[n + 1], sumP[n + 1], sumS[n + 1];
    sumH[0] = 0, sumP[0] = 0, sumS[0] = 0;

    for (int i = 0; i < n; i++) {
        char cur_choice; fin >> cur_choice;
        if (cur_choice == 'H') {
            sumH[i + 1] = 1 + sumH[i];
            sumP[i + 1] = sumP[i];
            sumS[i + 1] = sumS[i];
        }
        else if (cur_choice == 'P') {
            sumH[i + 1] = sumH[i];
            sumP[i + 1] = 1 + sumP[i];
            sumS[i + 1] = sumS[i];
        }
        else if (cur_choice == 'S') {
            sumH[i + 1] = sumH[i];
            sumP[i + 1] = sumP[i];
            sumS[i + 1] = 1 + sumS[i];
        }
    }



    int ans = 0;
    string choices = "HPS";
    for (char start : choices) {
        for (char end: choices) {
            if (start == 'H' && end == 'H') {
                ans = max(ans, sumH[n]);
            }
            else if (start == 'P' && end == 'P') {
                ans = max(ans, sumP[n]);
            }
            else if (start == 'S' && end == 'S') {
                ans = max(ans, sumS[n]);
            }
            else {
                for (int changing_time = 1; changing_time < n; changing_time++) {
                    //changing_time represents the first time that bessie will change
                    //          0 1 2 3 3 4 4
                    //for the ex: H H H P H P
                    //changing time is 3^ since 3 is the first time that bessie changes
                    int temp_won = 0;

                    if (start == 'H') {
                        //count the number of scissors
                        temp_won += sumS[changing_time + 1];
                    }
                    else if (start == 'P') {
                        //count the number of hoofs
                        temp_won += sumH[changing_time + 1];
                    }
                    else if (start == 'S') {
                        //count the number of papers
                        temp_won += sumP[changing_time + 1];
                    }

                    if (end == 'H') {
                        temp_won += sumS[n] - sumS[changing_time];
                    }
                    else if (end == 'P') {
                        temp_won += sumH[n] - sumH[changing_time];
                    }
                    else if (end == 'S') {
                        temp_won += sumP[n] - sumP[changing_time];
                    }

                    ans = max(ans, temp_won);
                }
            }
        }
    }
    fout << ans;
}