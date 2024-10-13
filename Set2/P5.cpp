#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    int x,y;
};

bool compareToX(const Point& a, const Point& b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool compareToY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double distance(Point& a, Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

void merge(vector<Point>& arr, int left, int right, int mid) {
    int leftSize = mid - left;
    int rightSize = right - mid;
    vector<Point> leftHalf(leftSize);
    vector<Point> rightHalf(rightSize);
    for (int i = 0; i < leftSize; ++i) {
        leftHalf[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; ++i) {
        rightHalf[i] = arr[mid + i];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while(i < leftSize && j < rightSize) {
        if (compareToY(leftHalf[i], rightHalf[j])) {
            arr[k] = leftHalf[i];
            ++i;
        } else {
            arr[k] = rightHalf[j];
            ++j;
        }
        ++k;
    }
    while(i < leftSize) {
        arr[k] = leftHalf[i];
        ++i;
        ++k;
    }
    while(j < rightSize) {
        arr[k] = rightHalf[j];
        ++j;
        ++k;
    }
}

double findClosest(vector<Point>& arr, int left, int right) {
    if (right - left <= 4) {
        double minDistance = 2e9;
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                double temp = distance(arr[i], arr[j]);
                minDistance = min(minDistance, temp);
            }
        }
        sort(arr.begin() + left, arr.begin() + right, compareToY);
        return minDistance;
    }
    int mid = (left + right) / 2;
    int midX = arr[mid].x;
    double leftD = findClosest(arr, left, mid);
    double rightD = findClosest(arr, mid, right);
    double d = min(leftD, rightD);

    merge(arr, left, right, mid);

    vector<Point> points;
    for (int i = left; i < right; ++i) {
        if (abs(arr[i].x - midX) < d) {
            points.push_back(arr[i]);
        }
    }

    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size() && (points[j].y - points[i].y) < d; ++j) {
            d = min(d, distance(points[j], points[i]));
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x,y;
    vector<Point> points;
    while(cin >> x >> y) {
        points.push_back({x,y});
    }
    sort(points.begin(), points.end(), compareToX);
    double ans = findClosest(points, 0, points.size());
    cout << (int)ans;
}