#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 300;
vector<int> dirty_cols_in_row[MAX_N]; // Similar to adjacency list for each left vertex in the graph
vector<int> match_row_to_col(MAX_N);  // This is similar to matched edges in the graph
vector<bool> checked(MAX_N);

bool can_clean_this_row(int row);

int main() {
    int n, m;
    cin >> n >> m;

    // Get input
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '#')
                dirty_cols_in_row[i].push_back(j);
        }
    }

    // A pair (j, match_row_to_col[j]) is column j and correspond matched row.
    for (int j = 0; j < m; j++)
        match_row_to_col[j] = -1;

    int result = 0;

    // Check all rows
    for (int i = 0; i < n; i++) {
        checked.assign(m, false);
        if (can_clean_this_row(i)) result++;
    }
    cout << result;

    return 0;
}

// DFS to find an augmenting path starting from a given row.
// Returns true if we can match this row to a column.
bool can_clean_this_row(int row) {
    for (int col : dirty_cols_in_row[row]) {
        if (!checked[col]) {
            checked[col] = true;

            // If column is free OR we can rematch the row currently matched to this column
            if (match_row_to_col[col] == -1 || can_clean_this_row(match_row_to_col[col])) {
                match_row_to_col[col] = row;
                return true;
            }
        }
    }
    return false;
}