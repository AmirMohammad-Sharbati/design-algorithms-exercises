#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {

    int n;
    cin >> n;

    // We need to maximize the weighted sums of first i numbers (sum(a1 to ai)): coefficients are (bi+1 - bi), so they are +-1 or 0
    long long sum; // sums of first i numbers

    // We need two heaps to have the numbers with coefficients +1 and -1
    priority_queue<long long> max_heap;
    priority_queue<long long, vector<long long>, greater<long long>> min_heap; // Min-heap

    float median;
    long long result = 0;
    long long max_heap_sum = 0;
    long long min_heap_sum = 0;

    cin >> sum;
    if (sum >= 0) {
        result += sum;
        min_heap.push(sum);
        min_heap_sum += sum;
    } else {
        result -= sum;
        max_heap.push(sum);
        max_heap_sum += sum;
    }

    cout << result << " ";

    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;

        sum += a;

        if (max_heap.size() == min_heap.size()) {
            median = (max_heap.top() + min_heap.top()) / 2;
        } else if (max_heap.size() > min_heap.size()) {
            median = max_heap.top();
        } else {
            median = min_heap.top();
        }

        if (sum <= median) {
            max_heap.push(sum);
            max_heap_sum += sum;
        } else {
            min_heap.push(sum);
            min_heap_sum += sum;
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