#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 'point' declaration -> It has five elements: which one is that (first, second, ..) by index and coordinate by x, y, z and the result
struct Point {
    int index, x, y, z, ans;
};


int main () {
    int n;
    cin >> n;

    vector<Point> all_points(n);

    for (int i = 0; i < n; i++) {
        all_points[i].index = i+1;
        cin >> all_points[i].x >> all_points[i].y >> all_points[i].z;
        all_points[i].ans = 0;
    }

    // At first, we sort the points by x:
    sort(all_points.begin(), all_points.end(), [](const Point &a, const Point &b) {
        return a.x < b.x;
    });

    // Now, we should declare recursive function (divide and conqure):




    // At the end we print the result by order of index (so we should sort it at first):
    sort(all_points.begin(), all_points.begin(), [](const Point &a, const Point &b){
        return a.index < b.index;
    }); 
    
    for (const Point &p : all_points)
        cout << p.ans << " ";

    return 0;
}