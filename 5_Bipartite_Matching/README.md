# Problem 5: Cleaning the Neighborhood

## 📋 Problem Statement

We have a grid of size `n × m` where each cell is either clean (`.`) or dirty (`#`). 

In each operation, we can:
- Choose a row and clean all dirty cells in that row
- Choose a column and clean all dirty cells in that column

We want to clean the entire neighborhood (all dirty cells) using the minimum number of operations.

**Input:**
- First line: `n` and `m` (rows and columns)
- Next `n` lines: grid with `.` and `#`

**Output:** Minimum number of operations needed

## 🧠 Algorithm

**Algorithm:** Maximum Bipartite Matching (Kőnig's Theorem)

This is a classic minimum vertex cover problem in bipartite graphs.

### Problem Reduction

We model the problem as a bipartite graph:
- **Left side:** Rows (n vertices)
- **Right side:** Columns (m vertices)
- **Edge:** Between row `i` and column `j` if cell `(i, j)` is dirty

Cleaning a row means selecting the row vertex, and cleaning a column means selecting the column vertex. We need to cover all edges (dirty cells) with the minimum number of vertices.

By **Kőnig's Theorem**, in bipartite graphs:  
Minimum Vertex Cover = Maximum Matching  


### Maximum Bipartite Matching (DFS-based)

We find the maximum matching using DFS (Kuhn's algorithm):
1. Try to match each row to a column
2. If a column is already matched, try to reassign (find augmenting path)
3. Count matches = minimum operations

### Complexity

**Time Complexity:** O(n × m) - each DFS visits each column at most once
**Space Complexity:** O(n + m) - storing graph and matching
