#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

struct Point {
    int x,y,z;
};

double distance(Point& a, Point& b) {
    return hypot(a.x - b.x, a.y - b.y, a.z - b.z);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Point> arr;
    for (int i = 0; i < n; ++i) {
        int x,y,z;
        cin >> x >> y >> z;
        arr.push_back({x,y,z,});
    }

    double minDistance = 2e9;
    int point1Ind = -1;
    int point2Ind = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double temp = distance(arr[i], arr[j]);
            if (temp < minDistance) {
                minDistance = temp;
                point1Ind = i + 1;
                point2Ind = j + 1;
            }
        }
    }
    cout << fixed << setprecision(6) << minDistance << '\n';
    cout << point1Ind << " " << point2Ind << "\n";
}