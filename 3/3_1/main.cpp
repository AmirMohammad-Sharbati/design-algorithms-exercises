#include <iostream>
#include <vector>

using namespace std;

vector<int> dirty_cols_in_row[300];       // Similar to adjascy list for each left vertex in the graph
vector<int> should_clean_row_in_col(300); // This is similar to matched edges in the graph

int main() {
    int n, m;
    cin >> n >> m;

    // Get input
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '#') {
                dirty_cols_in_row[i].push_back(j);
            }
        }
    }

    // int checked[m];

    for (int j = 0; j < m; j++) {
        should_clean_row_in_col[j] = -1;
    }

    int result = 0;

    // Check all rows
    for (int i = 0; i < n; i++) {
        // for (int j = 0; j < dirty_cols_in_row[i].size(); j++) {
        //     checked[j] = false;
        // }
        if (can_clean_this_row(i)) result++;
    }
    cout << result;

    return 0;
}

bool can_clean_this_row(int row) {
    for (int j = 0; j < dirty_cols_in_row[row].size(); j++) {
        if (should_clean_row_in_col[j] == -1 || can_clean_this_row(should_clean_row_in_col[should_clean_row_in_col[j]]))
            should_clean_row_in_col[j] = row;
        return true;
    }
    return false;
}