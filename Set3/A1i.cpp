#include <iostream>
#include <random>
using namespace std;

bool isInsideCircle(double x, double y, double cx, double cy, double r) {
    return (pow(x - cx, 2) + pow(y - cy, 2) <= pow(r, 2));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    double x1, y1, r1;
    double x2, y2, r2;
    double x3, y3, r3;
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    cin >> x3 >> y3 >> r3;
    double temp = min(y1 - r1, y2 - r2);
    double bottom = min(temp, y3 - r3);
    temp = min(x1 - r1, x2 - r2);
    double left = min(temp, x3 - r3);
    temp = max(y1 + r1, y2 + r2);
    double top = max(temp, y3 + r3);
    temp = max(x1 + r1, x2 + r2);
    double right = max(temp, x3 + r3);
    double norm = (right - left) * (top - bottom);
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<> distr_x(left, right);
    std::uniform_real_distribution<> distr_y(bottom, top);
    int n = 1000000;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        double x = distr_x(generator);
        double y = distr_y(generator);
        if (isInsideCircle(x1, y1, x, y, r1) &&
            isInsideCircle(x2, y2, x, y, r2) &&
            isInsideCircle(x3, y3, x, y, r3)) {
            ++k;
        }
    }
    double normArea = (static_cast<double>(k) / n) * norm;
    cout << normArea << '\n';
}