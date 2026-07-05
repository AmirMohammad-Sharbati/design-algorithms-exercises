# Problem 1: Lipschitz Sequence Maximum Weighted Sum

## 📋 Problem Statement

Given a sequence of `n` integers `a₁, a₂, ..., aₙ`, for each prefix of length `k` (1 ≤ k ≤ n), find the maximum possible value of:

Σᵢ₌₁ᵏ (aᵢ × bᵢ)

where bᵢ ∈ {-1, 0, 1} and |bᵢ₊₁ - bᵢ| ≤ 1. Also |b₁ - bₖ| ≤ 1.

- **Input:** n and then n numbers  
- **Output:** n numbers - the answer for each prefix

https://en.wikipedia.org/wiki/Lipschitz_continuity


## 🧠 Algorithm 

**Algorithm:** Greedy with Two Heaps (Online Median Partition)

The key trick is rewriting the sum:  
Σ(aᵢ × bᵢ) = (b₁-b₂)S₁ + (b₂-b₃)S₂ + ... + (bₖ₋₁-bₖ)Sₖ₋₁ + bₖSₖ


where Sᵢ = a₁ + a₂ + ... + aᵢ.

Each coefficient (bᵢ - bᵢ₊₁) is -1, 0, or 1. So we just need to assign these coefficients to prefix sums Sᵢ to maximize the total.

To maximize, we give:
- +1 to the largest Sᵢ
- -1 to the smallest Sᵢ
- 0 to the middle one (if needed)

We process numbers one by one and maintain two heaps:
- `min_heap`: stores the larger half (gets +1)
- `max_heap`: stores the smaller half (gets -1)

Each new Sᵢ goes to the correct heap based on median, then we rebalance. The answer is:  
sum(min_heap) - sum(max_heap)

With a small adjustment for the zero coefficient when heaps are equal size.

**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

You can see this code which implements two heaps to calculate the median and sum of numbers:
https://github.com/AmirMohammad-Sharbati/data-structures-and-algorithms/tree/master/T2_data_structures/1_heap


### Big note:
I implemented two versions of the code. They are both similar. In the first code, everything is in one main function. In the second, I implemented some functions to make the code cleaner. They are like macros (code snippets). To avoid passing values and returning them, I used global variables.