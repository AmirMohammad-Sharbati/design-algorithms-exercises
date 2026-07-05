# Problem 6: String Compression

## 📋 Problem Statement

We have a string of length `n`. We want to find the minimum possible length after compressing it using the following format:

- A substring `S` repeated `k` times can be written as `(S)k`
- For example: `cababdababd` can be compressed to `(c)1((ab)2d)2`
- Numbers in the compression don't take memory (they're just for representation)

We need to find the shortest compressed representation of the input string.

**Input:**
- First line: `n` (string length)
- Second line: the string

**Output:** Minimum length of the compressed string

## 🧠 Algorithm

**Algorithm:** Dynamic Programming

This is a classic string compression problem similar to "String Compression".

### DP State

Let `dp[i][j]` be the minimum compressed length of substring `s[i..j]`.

### Transitions

For each substring `s[i..j]`:
1. **Compression by repetition:** If the substring consists of a repeating pattern, we can compress it to the length of the pattern:
   - If length `len` is divisible by `k` and `s[i..j]` is `k` repetitions of `s[i..i+k-1]`
   - Then `dp[i][j] = dp[i][i+k-1]` (length of the pattern)

2. **Splitting:** We can split the substring at any point:
   - `dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid+1][j])`

We try all possible splits and all possible pattern lengths to find the minimum.

### Complexity

- **Time Complexity:** O(n³) - checking all substrings and all pattern lengths
- **Space Complexity:** O(n²) - DP table