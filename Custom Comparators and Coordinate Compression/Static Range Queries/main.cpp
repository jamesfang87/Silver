#include <iostream>
#include <vector>
#include <algorithm>


// i'm using a struct cuz why tf not ykyk
struct Range {
    int start, end, value = 0;
};


int compress(int i, std::vector<int> & indices) {
    return std::lower_bound(indices.begin(), indices.end(), i) - indices.begin();
}


int main() {
    // get all the shit we need to do the problem
    int num_updates, num_queries;
    std::cin >> num_updates >> num_queries;

    std::vector<int> special_indices;
    std::vector<Range> updates (num_updates);
    std::vector<Range> queries (num_queries);

    for (int i = 0; i < num_updates; i++) {
        int start, end, value;
        std::cin >> start >> end >> value;
        updates.at(i).start = start;
        updates.at(i).end = end;
        updates.at(i).value = value;

        special_indices.push_back(start);
        special_indices.push_back(end);
    }


    for (int i = 0; i < num_queries; i++) {
        int start, end;
        std::cin >> start >> end;
        queries.at(i).start = start;
        queries.at(i).end = end;

        special_indices.push_back(start);
        special_indices.push_back(end);
    }

    sort(special_indices.begin(), special_indices.end());
    special_indices.erase(std::unique(special_indices.begin(), special_indices.end()), special_indices.end());


    // use difference array
    std::vector<long long> difference_array (special_indices.size(), 0);
    std::vector<long long> interval_values (special_indices.size(), 0);
    std::vector<long long> prefix_sums (special_indices.size(), 0);


    for (Range update: updates) {
        int compressed_start = compress(update.start, special_indices);
        int compressed_end = compress(update.end, special_indices);
        difference_array.at(compressed_start) += update.value;
        difference_array.at(compressed_end) -= update.value;
    }


    for (int i = 1; i < interval_values.size(); i++) {
        interval_values.at(i) += interval_values.at(i - 1) + difference_array.at(i - 1);
    }

    // prefix sum interval_values[1:]
    for (int i = 1; i < prefix_sums.size(); i++) {
        prefix_sums.at(i) +=
                prefix_sums[i - 1] + interval_values.at(i) * (special_indices.at(i) - special_indices.at(i - 1));
    }

    for (int i = 0; i < num_queries; i++) {
        std::cout << prefix_sums[compress(queries.at(i).end, special_indices)] -
                     prefix_sums[compress(queries.at(i).start, special_indices)]
                     << '\n';
    }


}
