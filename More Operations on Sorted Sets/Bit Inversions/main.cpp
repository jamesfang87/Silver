#include <iostream>
#include <set>
using namespace std;

int main() {
    string bits; cin >> bits;

    set<int> segment_starts = {0, (int) bits.length()};
    for (int i = 1; i < bits.size(); i++) {
        if (bits[i] != bits[i - 1]) segment_starts.insert(i);
    }

    multiset<int> segment_lens;
    for (auto it = segment_starts.begin(); it != prev(segment_starts.end()); it++) {
        segment_lens.insert(*next(it) - *it);
    }

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int index; cin >> index; index--;

        auto end_iterator = segment_starts.upper_bound(index);
        auto start_iterator = prev(end_iterator);

        int segment_start = *start_iterator;
        int segment_end = *end_iterator;

        int segment_len = segment_end - segment_start;

        // index is the start of a segment
        if (segment_start == index) {
            segment_lens.erase(segment_lens.find(segment_len));

            int prev_segment_len = 0;
            if (start_iterator != segment_starts.begin())
                prev_segment_len = segment_start - *prev(start_iterator);

            if (segment_len == 1) {
                // get length of next segment

                int next_segment_len = 0;
                if (end_iterator != prev(segment_starts.end()))
                    next_segment_len = *next(end_iterator) - segment_end;

                // remove next and prev segment lengths
                auto it = segment_lens.find(prev_segment_len);
                if (it != segment_lens.end())
                    segment_lens.erase(it);

                it = segment_lens.find(next_segment_len);
                if (it != segment_lens.end())
                    segment_lens.erase(it);

                // insert merged length
                segment_lens.insert(prev_segment_len + next_segment_len + 1);
            } else {
                segment_lens.insert(segment_len - 1);

                auto it = segment_lens.find(prev_segment_len);
                if (it != segment_lens.end())
                    segment_lens.erase(it);

                segment_lens.insert(prev_segment_len + 1);
            }

            if (segment_start != 0)
                segment_starts.erase(start_iterator);

            if (segment_len == 1) {
                if (end_iterator != prev(segment_starts.end())) {
                    segment_starts.erase(end_iterator);
                }
            } else {
                segment_starts.insert(segment_start + 1);
            }
        } else {
            if (index == segment_end - 1) {
                segment_lens.erase(segment_lens.find(segment_len));
                segment_lens.insert(segment_len - 1);

                int next_segment_len = 0;
                if (end_iterator != prev(segment_starts.end()))
                    next_segment_len = *next(end_iterator) - segment_end;

                auto it = segment_lens.find(next_segment_len);
                if (it != segment_lens.end())
                    segment_lens.erase(it);
                segment_lens.insert(next_segment_len + 1);

                segment_starts.insert(index);
                if (end_iterator != prev(segment_starts.end())) {
                    segment_starts.erase(end_iterator);
                }
            } else {
                segment_lens.erase(segment_lens.find(segment_len));
                segment_lens.insert(index - segment_start);
                segment_lens.insert(segment_end - index - 1);
                segment_lens.insert(1);

                segment_starts.insert(index);
                segment_starts.insert(index + 1);
            }
        }

        cout << *segment_lens.rbegin() << ' ';
    }
}
