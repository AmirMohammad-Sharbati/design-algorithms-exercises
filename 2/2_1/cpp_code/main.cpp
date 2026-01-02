#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int id(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3; // T
}

char ch(int x) {
    return "ACGT"[x];
}

int main() {
    int n, m;
    cin >> n >> m;

    string input_genetic;
    cin >> input_genetic;

    unordered_map<string, long> genetic_patterns;
    unordered_map<string, long> new_string_values;

    genetic_patterns.reserve(m);
    for (int i = 0; i < m; i++) {
        string pattern;
        int value;
        cin >> pattern >> value;
        genetic_patterns.insert({pattern, value});
    }

    // key is three last characters of final string
    unordered_map<string, long> prev_string_values; // 64 is 4^3, three last alphabets of string
    char alphabets[4] = {'A', 'C', 'G', 'T'};

    vector<unordered_map<string, string>> parent_state(n);
    vector<unordered_map<string, char>> parent_char(n);

    for (char c : (input_genetic[0] == '?' ? alphabets : string(1, input_genetic[0]))) {
        long score = 0;
        string key = string(1, c);

        if (genetic_patterns.count(key)) score += genetic_patterns[key];

        parent_char[0][key] = c;
        parent_state[0][key] = "";
        prev_string_values[key] = score; // only one char
    }

    for (int k = 1; k < n; k++) {
        new_string_values.clear();
        for (auto iterator = prev_string_values.begin(); iterator != prev_string_values.end(); iterator++) {
            string prev = iterator->first;
            long prev_score = iterator->second;

            for (char alphabet : (input_genetic[k] == '?' ? alphabets : string(1, input_genetic[k]))) {
                long value = prev_score;
                string key = prev + alphabet;

                for (int len = 1; len <= (int)key.size(); len++) {
                    string suffix = key.substr((int)key.size() - len, len);
                    if (genetic_patterns.count(suffix)) {
                        value += genetic_patterns[suffix];
                    }
                }

                // new_string_values.insert({string(1, c2) + c3 + alphabet, iterator->second + value});
                // string next_state = key.substr(1, 3);
                string next_state;
                if ((int)key.size() <= 3)
                    next_state = key;
                else
                    next_state = key.substr(key.size() - 3);

                if (!new_string_values.count(next_state) || value > new_string_values[next_state]) {
                    new_string_values[next_state] = value;
                    parent_state[k][next_state] = iterator->first; // previous 3-char state
                    parent_char[k][next_state] = alphabet;         // appended char
                }
            }
        }
        prev_string_values = new_string_values;
    }


    long max_value = -1e18;
    string last_state;

    for (auto &p : prev_string_values) {
        if (p.second > max_value) {
            max_value = p.second;
            last_state = p.first;
        }
    }

    string answer;
    string cur_state = last_state;

    for (int k = n - 1; k >= 0; k--) {
        char c = parent_char[k][cur_state];
        answer.push_back(c);
        cur_state = parent_state[k][cur_state];
    }

    reverse(answer.begin(), answer.end());

    cout << max_value << endl;
    cout << answer;
    return 0;
}