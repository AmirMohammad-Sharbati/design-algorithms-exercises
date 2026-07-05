# Problem 4: Non-Descending Sequences


## 📋 Problem Statement

We need to construct a non-decreasing sequence of length `n` where each element is between `1` and `m`:  
1 ≤ A₁ ≤ A₂ ≤ ... ≤ Aₙ ≤ m

We are also given `q` constraints. Each constraint has four values `(a, b, c, d)` meaning: 
- If `A_b - A_a = c`, then add `d` to the total score

The goal is to find a valid sequence that maximizes the total score.

**Input:**
- First line: `n`, `m`, `q`
- Next `q` lines: `a`, `b`, `c`, `d`

**Output:** Maximum possible score

## 🧠 Algorithm

**Algorithm:** Brute Force + DFS

Since `n ≤ 10` and `m ≤ 10`, the number of non-decreasing sequences is small enough to generate all of them.

### Counting Sequences

The number of non-decreasing sequences of length `n` with values from `1` to `m` is:  
C(n + m - 1, n)



For maximum values `n = 10` and `m = 10`, this is `C(19, 10) = 92,378` sequences. This is small enough to check all of them.

### DFS Generation

We generate all non-decreasing sequences recursively:
- Start with `1` as the first element
- At each step, the next element must be ≥ the previous element
- Continue until we reach length `n`

### Checking Constraints

For each generated sequence:
1. Initialize score = 0
2. For each constraint `(a, b, c, d)`:
   - If `sequence[b-1] - sequence[a-1] == c`, add `d`
3. Keep track of maximum score

### Complexity

**Time Complexity:** O(C(n+m-1, n) × q) - generating all sequences and checking constraints
**Space Complexity:** O(C(n+m-1, n) × n) - storing all sequences

## Files

- `main.cpp`: C++ implementation
- `Main.java`: Java implementation
- `main.py`: Python implementation
