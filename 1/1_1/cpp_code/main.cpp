#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Function delcaration
void doing_first_push();
void rebalancing_heaps();
void median_calculation();
void result_calculation();
void push_to_correct_heap();

// We need two heaps to have the numbers with coefficients +1 (min_heap) and -1 (max_heap)
priority_queue<long long> max_heap;
priority_queue<long long, vector<long long>, greater<long long>> min_heap;
long long result = 0;
long long max_heap_sum = 0;
long long min_heap_sum = 0;
float median;
long long sum; // sum of first i numbers

// We need to maximize the weighted sums of first i numbers (sum(a1 to ai)): coefficients are (bi+1 - bi), so they are +-1 or 0
int main() {
    int n;
    cin >> n;

    cin >> sum;
    doing_first_push();

    cout << result << " ";

    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;
        sum += a;

        median_calculation();
        push_to_correct_heap();

        rebalancing_heaps();
        result_calculation();

        cout << result << " ";
    }

    return 0;
}

// This function is used only for first number insertion:
void doing_first_push() {
    if (sum >= 0) {
        result += sum;
        min_heap.push(sum);
        min_heap_sum += sum;
    } else {
        result -= sum;
        max_heap.push(sum);
        max_heap_sum += sum;
    }
}

// This function calculates median of numbers:
void median_calculation() {
    if (max_heap.size() == min_heap.size()) {
        median = (max_heap.top() + min_heap.top()) / 2;
    } else if (max_heap.size() > min_heap.size()) {
        median = max_heap.top();
    } else {
        median = min_heap.top();
    }
}

// This function rebalance heaps. Their size differ at most one:
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

// Based on median we should insert the number to correct heap:
void push_to_correct_heap() {
    if (sum <= median) {
        max_heap.push(sum);
        max_heap_sum += sum;
    } else {
        min_heap.push(sum);
        min_heap_sum += sum;
    }
}

// This function calculate the k'th final result
void result_calculation() {
    // Assign coefficien -1 to max_heap numbers (half that are small) and +1 to min_heap numbers (bigger numbers):
    result = min_heap_sum - max_heap_sum;

    // We can make it a little better by assiging zero or change -1 to +1 or vise versa when we can do it.
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