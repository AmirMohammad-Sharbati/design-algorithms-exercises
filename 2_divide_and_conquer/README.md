# Problem 2: 3D Dominance Counting

## Problem Statement

Given `n` points in 3D space `(xᵢ, yᵢ, zᵢ)`, for each point we need to count how many other points are strictly dominated in all three dimensions:  
ansᵢ = |{(xⱼ, yⱼ, zⱼ) | xⱼ < xᵢ and yⱼ < yᵢ and zⱼ < zᵢ}|

All coordinates are unique (no two points share the same x, y, or z).

- **Input:** n and then n points (x, y, z)  
- **Output:** ans for each point in input order


## 🧠 Algorithm

**Algorithm:** Divide and Conquer + Fenwick Tree (BIT)  
The brute force O(n²) solution compares every pair of points. We need O(n log² n).  

### Fenwick Tree (BIT)

We use a Fenwick tree to maintain counts of z values from the left half:
- `add_to_seen_z(z)`: adds 1 at position z
- `count_z_less_than_current(z)`: returns sum of counts from positions 1 to z

Since we clear the tree for each recursion level, we use `last_seen` array to avoid reinitializing the whole tree (optimization).

You can see good and complete explanations in [this link](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.youtube.com/watch%3Fv%3DuSFzHCZ4E-8&ved=2ahUKEwizjOCE5KORAxWY0QIHHVOrEQ8QkPEHegQIGRAB&usg=AOvVaw0WY_BHKWkAdJGwRZpGcNUu)


### Main Idea

1. **Sort by x:** Points are sorted by x coordinate.
2. **Divide:** Split the sorted array into two halves.
3. **Conquer:** Recursively solve for left and right halves.
4. **Combine:** Points in the right half have larger x than points in the left half. So for each point in the right half, we only need to count points in the left half with smaller y and z.


### The Combine Step

For the right half, we need to count how many points in the left half have:
- y < current_y
- z < current_z

We process both halves sorted by y:
- Iterate through right half points (by increasing y)
- Add left half points with smaller y to a Fenwick tree (indexed by z)
- Query the tree for count of points with z < current_z

This gives us the dominance count for the combine step.  

### Complexity

- **Time Complexity:** O(n log² n)  
- **Space Complexity:** O(n)