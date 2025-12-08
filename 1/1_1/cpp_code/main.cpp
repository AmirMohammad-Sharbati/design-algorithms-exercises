#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {

    int n;
    cin >> n;

    // We need to maximize the weighted sums of first i numbers (sum(a1 to ai)): coefficients are (bi+1 - bi), so they are +-1 or 0
    vector<int> sums(n); // sums of first i numbers
    int median;

    // We need two heaps to have the numbers with coefficients +1 and -1
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap; // Min-heap

    int result = 0;
    int max_heap_sum = 0;
    int min_heap_sum = 0;

    cin >> sums[0];
    if (sums[0] >= 0) {
        result += sums[0];
        min_heap.push(sums[0]);
        min_heap_sum += sums[0];
    } else {
        result -= sums[0];
        max_heap.push(sums[0]);
        max_heap_sum += sums[0];
    }

    cout << result << " ";

    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;

        sums[i] = a + sums[i - 1];

        if (max_heap.size() == min_heap.size()) {
            median = (max_heap.top() + min_heap.top()) / 2;
        } else if (max_heap.size() > min_heap.size()) {
            median = max_heap.top();
        } else {
            median = min_heap.top();
        }

        if (sums[i] <= median) {
            max_heap.push(sums[i]);
            max_heap_sum += sums[i];
        } else {
            min_heap.push(sums[i]);
            min_heap_sum += sums[i];
        }

        // Rebalance heaps
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            min_heap_sum += max_heap.top();
            max_heap_sum -= max_heap.top();
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size() + 1) {
            max_heap.push(min_heap.top());
            max_heap_sum += min_heap.top();
            min_heap_sum -= min_heap.top();
            min_heap.pop();
        }

        result = min_heap_sum - max_heap_sum;

        if (max_heap.size() == min_heap.size()) {
            if (max_heap.top() > 0)
                result += max_heap.top();
            else if (min_heap.top() < 0)
                result -= min_heap.top();
        } else if (max_heap.size() > min_heap.size()) {
            if (max_heap.top() > 0) {
                result += 2 * max_heap.top();
            }
        } else {
            if (min_heap.top() < 0) {
                result -= 2 * min_heap.top();
            }
        }

        cout << result << " ";
    }

    return 0;
}