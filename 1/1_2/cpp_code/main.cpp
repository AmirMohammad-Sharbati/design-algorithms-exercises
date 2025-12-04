#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void dominance_counting(int l, int r);
void add_to_seen_z(int z);
int count_z_less_than_current(int z);

// 'point' declaration -> It has five elements: which one is that (first, second, ..) by index and coordinate by x, y, z and the result:
struct Point {
    int index, x, y, z, ans;
};

// These are global variables, because they are used many times:
vector<Point> all_points;
vector<int> seen_z;

int main() {
    int n;
    cin >> n;

    all_points.resize(n);

    vector<int> z_values(n);

    for (int i = 0; i < n; i++) {
        all_points[i].index = i + 1;
        cin >> all_points[i].x >> all_points[i].y >> all_points[i].z;
        z_values[i] = all_points[i].z;
        all_points[i].ans = 0;
    }

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
    sort(all_points.begin(), all_points.begin(), [](const Point &a, const Point &b) {
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

    // Main idea of algorithm (merge step):
    vector<Point> left, right;
    for (int i = l; i <= mid; i++)
        left.push_back(all_points[i]);
    for (int i = mid + 1; i <= r; i++)
        right.push_back(all_points[i]);

    // Now I should sort points based on y:
    sort(left.begin(), left.end(), [](auto &a, auto &b) {
        return a.y < b.y;
    });
    sort(right.begin(), right.end(), [](auto &a, auto &b) {
        return a.y < b.y;
    });

    // seen_z is global variable. It is necessary to reinitialize it to zero (and we can also resize it, both wit resize() function):
    seen_z.resize((mid - l + 2), 0);

    // We only need to iterate over right array and use BIT for finding the count of (z in left array < current z):
    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        while (j <= mid && left[j].y < right[i].y) {
            add_to_seen_z(left[j].z);
            j++;
        }
        right[i].ans += count_z_less_than_current(right[i].z);
    }
}

void add_to_seen_z(int z) {
    for (int i = z; i <= seen_z.size(); i += i & (-i))
        seen_z[i] += 1;
}

int count_z_less_than_current(int z) {
    int sum = 0;
    for (int i = z; i > 0; i -= i & (-i))
        sum += seen_z[i];
    return sum;
}