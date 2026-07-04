#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void dominance_counting(int l, int r);
void add_to_seen_z(int z);
int count_z_less_than_current(int z);

// 'point' declaration -> It has five elements: which one is that (first, second, ..) by index, coordinate by x, y, z and the result:
struct Point {
    int index, x, y, z, ans;
};

// These are global variables, because they are used many times:
vector<Point> all_points, temp; // temp for merge step in recursive function
vector<int> seen_z, last_seen;  // This is for BIT step
int n, exe_count;               // exe_count is for implementing the functionality to make the seen_z zero in next round of recursion

int main() {
    cin >> n;

    all_points.resize(n);
    temp.resize(n);

    vector<int> z_values(n);

    for (int i = 0; i < n; i++) {
        all_points[i].index = i + 1;
        cin >> all_points[i].x >> all_points[i].y >> all_points[i].z;
        z_values[i] = all_points[i].z;
        all_points[i].ans = 0;
    }

    seen_z.assign(n + 1, 0);
    last_seen.assign(n + 1, 0);
    exe_count = 1;

    // At first, because of later BIT structure, we need to compress the zs to numbers 1 to n based on thier order:
    sort(z_values.begin(), z_values.end());
    for (auto &p : all_points)
        p.z = lower_bound(z_values.begin(), z_values.end(), p.z) - z_values.begin() + 1;
    // lower_bound() finds the first element >= target in a sorted array (returns pointer to that element)

    // Then, we sort the points by x:
    sort(all_points.begin(), all_points.end(), [](const Point &a, const Point &b) {
        return a.x < b.x;
    });

    // Now, we should declare recursive function (divide and conqure approach):
    dominance_counting(0, n - 1);

    // At the end we print the result by order of index (so we should sort it at first by indexes):
    sort(all_points.begin(), all_points.end(), [](const Point &a, const Point &b) {
        return a.index < b.index;
    });

    for (const Point &p : all_points)
        cout << p.ans << " ";

    return 0;
}

void dominance_counting(int l, int r) {
    if (l == r) return;

    int mid = (l + r) / 2;
    dominance_counting(l, mid);
    dominance_counting(mid + 1, r);

    /// Main idea of algorithm is this step (conqure step):

    // seen_z is global variable. It is necessary to reinitialize it to zero
    exe_count++;

    // We should sort points by y, but they are already sorted because of merges in previous rounds (See last 20 lines of this function).

    // We only need to iterate over right array and use BIT for finding the count of (z in left array < current z in right):
    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        while (j <= mid && all_points[j].y < all_points[i].y) {
            add_to_seen_z(all_points[j].z);
            j++;
        }
        all_points[i].ans += count_z_less_than_current(all_points[i].z);
    }

    // At the end we should merge these two sorted arrays:

    // Merge all_points[l..mid] and all_points[mid+1..r] by y into temp
    int i = l, k = l;
    j = mid + 1;

    while (i <= mid && j <= r) {
        if (all_points[i].y <= all_points[j].y)
            temp[k++] = all_points[i++];
        else
            temp[k++] = all_points[j++];
    }

    while (i <= mid)
        temp[k++] = all_points[i++];
    while (j <= r)
        temp[k++] = all_points[j++];

    // We should copy temp back to all_points
    for (int t = l; t <= r; t++)
        all_points[t] = temp[t];
}

// These two functions are related to the BIT (Fenwick) tree. It is amazing data structure :)

// We should updata specific numbers (i += i & (-i)):
void add_to_seen_z(int z) {
    for (int i = z; i <= n; i += i & (-i)) {
        if (last_seen[i] != exe_count) {
            last_seen[i] = exe_count;
            seen_z[i] = 0;
        }
        seen_z[i] += 1;
    }
}

// We should sum specific numbers to reach our goal (i -= i & (-i)):
int count_z_less_than_current(int z) {
    int sum = 0;
    for (int i = z; i > 0; i -= i & (-i)) {
        if (last_seen[i] != exe_count) {
            last_seen[i] = exe_count;
            seen_z[i] = 0;
        }
        sum += seen_z[i];
    }
    return sum;
}