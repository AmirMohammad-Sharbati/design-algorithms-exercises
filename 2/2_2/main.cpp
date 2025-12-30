#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> generateNonDescendantSequence(int length, int bound);

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    int a, b, c, d;
    vector<vector<int>> constraints;
    for (int i = 0; i < q; i++) {
        cin >> a >> b >> c >> d;
        constraints.push_back({a, b, c, d});
    }

    vector<vector<int>> allNonDescendantSequences = generateNonDescendantSequence(n, m);

    int maxValue = 0;
    for (vector<int> sequence : allNonDescendantSequences) {
        int value = 0;
        for (int i = 0; i < q; i++) {
            vector<int> constraint = constraints[i];
            if (sequence[constraint[1] - 1] - sequence[constraint[0] - 1] == constraint[2])
                value += constraint[3];
        }
        if (value > maxValue) maxValue = value;
    }

    cout << maxValue;

    return 0;
}

vector<vector<int>> generateNonDescendantSequence(int length, int bound) {
    if (length == 1) {
        vector<vector<int>> base_sequence;
        for (int i = 1; i <= bound; i++)
            base_sequence.push_back({i});
        return base_sequence;
    }

    vector<vector<int>> prevSequences;
    vector<vector<int>> finalSequences;

    prevSequences = generateNonDescendantSequence(length - 1, bound);

    for (vector<int> sequence : prevSequences) {
        for (int k = sequence.back(); k <= bound; k++) {
            vector<int> newSequence = sequence;
            newSequence.push_back(k);
            finalSequences.push_back(newSequence);
        }
    }

    return finalSequences;
}