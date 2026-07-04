#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const long long NEG_INF = -(1e16);

int id(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3; // T
}

int main() {
    int n, m;
    cin >> n >> m;

    string input_genetic;
    cin >> input_genetic;

    vector<array<int, 4>> next;
    vector<int> fail;
    vector<long long> value;

    next.push_back({-1, -1, -1, -1});
    fail.push_back(0);
    value.push_back(0);

    for (int i = 0; i < m; i++) {
        string pattern;
        long long value_i;
        cin >> pattern >> value_i;

        int u = 0;
        for (char alphabet : pattern) {
            int k = id(alphabet);
            if (next[u][k] == -1) {
                next[u][k] = next.size();
                next.push_back({-1, -1, -1, -1});
                fail.push_back(0);
                value.push_back(0);
            }
            u = next[u][k];
        }
        value[u] += value_i;
    }

    int nodes = next.size();

    queue<int> q;
    for (int c = 0; c < 4; c++) {
        if (next[0][c] == -1)
            next[0][c] = 0;
        else {
            fail[next[0][c]] = 0;
            q.push(next[0][c]);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        value[u] += value[fail[u]];

        for (int c = 0; c < 4; c++) {
            if (next[u][c] == -1)
                next[u][c] = next[fail[u]][c];
            else {
                fail[next[u][c]] = next[fail[u]][c];
                q.push(next[u][c]);
            }
        }
    }

    vector<long long> dp_cur(nodes, NEG_INF);
    vector<long long> dp_next(nodes, NEG_INF);

    vector<vector<int16_t>> parent(n + 1, vector<int16_t>(nodes, -1));
    vector<vector<char>> parent_char(n + 1, vector<char>(nodes, -1));

    dp_cur[0] = 0;

    vector<int> chars_to_use;
    for (int i = 0; i < n; i++) {
        chars_to_use.clear();
        fill(dp_next.begin(), dp_next.end(), NEG_INF);

        if (input_genetic[i] == '?')
            chars_to_use = {0, 1, 2, 3};
        else
            chars_to_use = {id(input_genetic[i])};

        for (int state = 0; state < nodes; state++) {
            if (dp_cur[state] == NEG_INF) continue;
            for (int alphabet : chars_to_use) {
                int next_state = next[state][alphabet];

                long long candidate = dp_cur[state] + value[next_state];
                if (candidate > dp_next[next_state]) {
                    dp_next[next_state] = candidate;
                    parent[i + 1][next_state] = state;
                    parent_char[i + 1][next_state] = alphabet;
                }
            }
        }

        swap(dp_cur, dp_next);
    }

    long long final_value = NEG_INF;
    int best_state = 0;

    for (int i = 0; i < nodes; i++) {
        if (dp_cur[i] > final_value) {
            final_value = dp_cur[i];
            best_state = i;
        }
    }

    string result;
    int current = best_state;

    for (int i = n; i > 0; i--) {
        int c = parent_char[i][current];
        result.push_back("ACGT"[c]);
        current = parent[i][current];
    }

    reverse(result.begin(), result.end());

    cout << final_value << "\n"
         << result;

    return 0;
}
