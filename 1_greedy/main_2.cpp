#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Function declarations
void doing_first_push();
void rebalancing_heaps();
void median_calculation();
void result_calculation();
void push_to_correct_heap();

// We use two heaps to store numbers assigned coefficients +1 (min_heap) and -1 (max_heap)
priority_queue<long long> max_heap;
priority_queue<long long, vector<long long>, greater<long long>> min_heap;
long long result = 0;
long long max_heap_sum = 0;
long long min_heap_sum = 0;
float median;
long long prefix_sum;

// We maximize the weighted sum of the first i numbers (sum(a1 to ai)). The coefficients are (bi+1 - bi), so they are ±1 or 0.
int main() {
    int n;
    cin >> n;

    cin >> prefix_sum;
    doing_first_push();

    cout << result << " ";

    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;
        prefix_sum += a;

        median_calculation();
        push_to_correct_heap();

        rebalancing_heaps();
        result_calculation();

        cout << result << " ";
    }

    return 0;
}

// This function handles only the first number insertion:
void doing_first_push() {
    if (prefix_sum >= 0) {
        result += prefix_sum;
        min_heap.push(prefix_sum);
        min_heap_sum += prefix_sum;
    } else {
        result -= prefix_sum;
        max_heap.push(prefix_sum);
        max_heap_sum += prefix_sum;
    }
}

// This function calculates the median of the numbers:
void median_calculation() {
    if (max_heap.size() == min_heap.size()) {
        median = (max_heap.top() + min_heap.top()) / 2;
    } else if (max_heap.size() > min_heap.size()) {
        median = max_heap.top();
    } else {
        median = min_heap.top();
    }
}

// This function rebalances the heaps. Their sizes should differ by at most one:
void rebalancing_heaps() {
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
}

// Based on the median, we insert the number into the correct heap:
void push_to_correct_heap() {
    if (prefix_sum <= median) {
        max_heap.push(prefix_sum);
        max_heap_sum += prefix_sum;
    } else {
        min_heap.push(prefix_sum);
        min_heap_sum += prefix_sum;
    }
}

// This function calculates the k-th final result:
void result_calculation() {
    // Assign coefficient -1 to max_heap numbers (the smaller half) and +1 to min_heap numbers (the larger half):
    result = min_heap_sum - max_heap_sum;

    // We can improve the result slightly by assigning zero, or changing -1 to +1 (or vice versa) when allowed.
    if (max_heap.size() == min_heap.size()) {
        if (max_heap.top() > 0)
            result += max_heap.top();
        else if (min_heap.top() < 0)
            result -= min_heap.top();
    } else if (max_heap.size() > min_heap.size()) {
        if (max_heap.top() > 0)
            result += 2 * max_heap.top();
    } else {
        if (min_heap.top() < 0)
            result -= 2 * min_heap.top();
    }
}