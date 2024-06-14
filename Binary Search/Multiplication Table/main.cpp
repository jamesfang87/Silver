#include <iostream>
using namespace std;

long long n;

long long f(long long x) {
    // with an n by n multiplication table flattened into a 1-d array and sorted in increasing order
    // return the number of elements not greater than x
    long long num = 0;
    for (int i = 1; i <= n; i++) {
        num += min(n, x / i);
    }
    return num;
}

int main() {
    cin >> n;

    // let's pretend to flatten and sort the multiplication table so that it is a 1-D array of length n^2
    // define a function f(x) to be the amount of numbers in the table which are not greater than x
    // then, if we take f(median), then we will for sure get the first half of this array plus the median
    // we can quickly verify that the value of f(median) is floor(n^2 / 2) + 1
    // we may also get a larger value from f(median); note the following case:
    // array = [..., 3, 3, 3, ...]
    // here 3 is the median but because there is another 3 after it, f(median) will return a value greater than
    // floor(n^2 / 2) + 1
    // thus, we can use binary search to find the smallest value of x such that f(x) >= floor(n^2 / 2) + 1

    // to implement f(x), we might naively loop over all values in the table, but that is too slow
    // we could use binary search for O(nlogn) solution, but in fact, there is a linear solution
    // note that for each row/column, the values in such row/column increase by a set amount, epsilon
    // intuitively, we can simply divide x by epsilon to find how many numbers are less than x in a row/column
    // then we can sum up that number for all rows/columns

    long long low = 0, high = n * n + 1;
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (f(mid) >= (n * n + 1) / 2) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    cout << low;
}