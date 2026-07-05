# Problem 3: DNA Sequence Design

## 📋 Problem Statement

We need to construct a DNA sequence of length `n` using nucleotides `{A, C, G, T}`. 

We have:
- A **stability pattern** of length `n` consisting of letters `{A, C, G, T, ?}`:
  - If the pattern has a specific letter, our sequence must have that exact letter at that position
  - If the pattern has `?`, we can choose any nucleotide

- A list of **genetic patterns** with scores (can be positive or negative). Each time a pattern appears in our sequence, we add its score. All occurrences count (even overlapping).

We need to find a sequence of length `n` that:
1. Matches the stability pattern
2. Maximizes the total score from genetic patterns
3. If multiple solutions exist, print any

**Input:**
- First line: `n` (sequence length) and `m` (number of genetic patterns)
- Second line: stability pattern of length `n`
- Next `m` lines: pattern string and its score value

**Output:**
- First line: maximum possible score
- Second line: the constructed sequence (any optimal one)

## 🧠 Algorithm

**Algorithm:** Aho-Corasick + Dynamic Programming

This is a classic string matching + DP problem with constraints on the sequence.

### Aho-Corasick Automaton

We build an Aho-Corasick automaton from all genetic patterns:
- Each node represents a prefix of some pattern
- `next[state][char]` gives the next state after adding character
- `fail[state]` gives the longest proper suffix that is also a prefix
- `value[state]` stores the total score of all patterns ending at this state (including fail links)

This allows us to efficiently track which patterns match as we build the sequence.

### Dynamic Programming

We use DP to find the optimal sequence:

**State:** `dp[i][state]` = maximum score after processing `i` characters and ending at automaton state `state`

**Transition:** For position `i` (0-indexed):
- If pattern has letter, try only that letter
- If pattern has `?`, try all 4 nucleotides
- For each valid character, move to `next_state = next[state][char]`
- New score = `dp[i][state] + value[next_state]`

We also store parent pointers to reconstruct the sequence.

**Base case:** `dp[0][0] = 0` (starting at root state)

**Answer:** Maximum value in `dp[n][*]`

### Complexity

**Time Complexity:** O(n × nodes × 4) - nodes is the total length of all patterns
**Space Complexity:** O(n × nodes) for DP table and parent pointers
