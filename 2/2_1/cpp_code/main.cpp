#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void update_three_final_values(char c1, char c2, char c3, char alphabet, unordered_map<string, int>::iterator iterator);

unordered_map<string, long> genetic_patterns;
unordered_map<string, long> new_string_values;

int main() {
    int n, m;
    cin >> n >> m;

    string input_genetic;
    cin >> input_genetic;

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

    char c1 = input_genetic[0];
    if (c1 != '?') {
        string key = string(1, c1);
        if (genetic_patterns.count(key)) {
            prev_string_values.insert({key, genetic_patterns[key]});
        } else
            prev_string_values.insert({key, 0});
    } else {
        for (char c1 : alphabets) {
            string key = string(1, c1);
            if (genetic_patterns.count(key)) {
                prev_string_values.insert({key, genetic_patterns[key]});
            } else
                prev_string_values.insert({key, 0});
        }
    }

    if (n >= 2) {
    }
    if (n >= 3) {
    }

    // ------------------
    // k = 0: first character
    // ------------------
    for (char c : (input_genetic[0] == '?' ? alphabets : string(1, input_genetic[0]))) {
        long score = 0;
        string key = string(1, c);

        if (genetic_patterns.count(key)) score += genetic_patterns[key];

        prev_string_values[key] = score; // only one char
    }

    // ------------------
    // k = 1: second character
    // ------------------
    new_string_values.clear();
    for (auto it = prev_string_values.begin(); it != prev_string_values.end(); ++it) {
        string prev = it->first;
        long prev_score = it->second;

        for (char c : (input_genetic[1] == '?' ? alphabets : string(1, input_genetic[1]))) {
            string key = prev + c; // two letters
            long score = prev_score;

            // add pattern scores ending here
            if (genetic_patterns.count(key)) score += genetic_patterns[key];                   // length 2
            if (genetic_patterns.count(string(1, c))) score += genetic_patterns[string(1, c)]; // length 1

            new_string_values[key] = max(new_string_values[key], score);
        }
    }
    prev_string_values = new_string_values;

    // ------------------
    // k = 2: third character
    // ------------------
    new_string_values.clear();
    for (auto it = prev_string_values.begin(); it != prev_string_values.end(); ++it) {
        string prev = it->first; // length 2
        long prev_score = it->second;

        for (char c : (input_genetic[2] == '?' ? alphabets : string(1, input_genetic[2]))) {
            string key = prev + c; // three letters
            long score = prev_score;

            // add pattern scores ending here (length 1..3)
            if (genetic_patterns.count(key)) score += genetic_patterns[key];                                     // length 3
            if (genetic_patterns.count(prev.substr(1, 1) + c)) score += genetic_patterns[prev.substr(1, 1) + c]; // length 2
            if (genetic_patterns.count(string(1, c))) score += genetic_patterns[string(1, c)];                   // length 1

            new_string_values[key] = max(new_string_values[key], score);
        }
    }
    prev_string_values = new_string_values;

    for (int k = 3; k < n; k++) {
        for (auto iterator = prev_string_values.begin(); iterator != prev_string_values.end(); iterator++) {
            char c1 = iterator->first[0];
            char c2 = iterator->first[1];
            char c3 = iterator->first[2];

            for (char alphabet : (input_genetic[k] == '?' ? alphabets : string(1, input_genetic[k]))) {
                int value = 0;
                string key = string(1, c1) + c2 + c3 + alphabet;
                if (genetic_patterns.count(key)) {
                    value += genetic_patterns[key];
                }
                key = string(1, c2) + c3 + alphabet;
                if (genetic_patterns.count(key)) {
                    value += genetic_patterns[key];
                }
                key = string(1, c3) + alphabet;
                if (genetic_patterns.count(key)) {
                    value += genetic_patterns[key];
                }
                key = string(1, alphabet);
                if (genetic_patterns.count(key)) {
                    value += genetic_patterns[key];
                }

                new_string_values.insert({string(1, c2) + c3 + alphabet, iterator->second + value});
            }

            // if (input_genetic[k] != '?')
            //     update_three_final_values(c1, c2, c3, input_genetic[k], iterator);
            // else {
            //     for (char alphabet : alphabets)
            //         update_three_final_values(c1, c2, c3, alphabet, iterator);
            // }
        }
        prev_string_values = new_string_values;
        new_string_values.clear();
    }

    long max_value = long(-1e14);
    for (const auto &p : prev_string_values)
        max_value = max(max_value, p.second);

    cout << max_value;
    return 0;
}

// void update_three_final_values(char c1, char c2, char c3, char alphabet, unordered_map<string, long>::iterator iterator) {
//     int value = 0;
//     string key = string(1, c1) + c2 + c3 + alphabet;
//     if (genetic_patterns.count(key)) {
//         value += genetic_patterns[key];
//     }
//     key = string(1, c2) + c3 + alphabet;
//     if (genetic_patterns.count(key)) {
//         value += genetic_patterns[key];
//     }
//     key = string(1, c3) + alphabet;
//     if (genetic_patterns.count(key)) {
//         value += genetic_patterns[key];
//     }
//     key = string(1, alphabet);
//     if (genetic_patterns.count(key)) {
//         value += genetic_patterns[key];
//     }

//     new_string_values.insert({string(1, c2) + c3 + alphabet, iterator->second + value});
// }