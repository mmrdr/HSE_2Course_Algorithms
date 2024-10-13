#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct Interval {
    long long t, v;
};

long double findDistance(const vector<Interval>& table, long double time) {
    long double distance = 0;
    long double passTime = 0;
    int dop = 0;
    for (const Interval& intrl : table) {
        if (passTime + intrl.t <= time) {
            distance += intrl.t * intrl.v;
            passTime += intrl.t;
            ++dop;
        } else {
            break;
        }
    }
    if (passTime < time) distance += (time - passTime) * table[dop].v;
    return distance;
}

bool check(const vector<Interval>& table, long long L, long double time) {
    if (findDistance(table, time) < L) {
        return false;
    }
    long double firstTrainDistance = 0;
    long double firstTrainTime = 0;
    long double secondTrainDistance = 0;
    for (const Interval& intrl : table) {
        firstTrainTime += intrl.t;
        firstTrainDistance += intrl.t * intrl.v;
        if (firstTrainTime < time) {
            continue;
        }
        secondTrainDistance = findDistance(table, firstTrainTime - time);
        if (firstTrainDistance - secondTrainDistance < L) {
            return false;
        }
    }
    return true;
}

long double findMinL(const vector<Interval>& table, long long L) {
    long double left = 0;
    long double right = 2e9;
    for (int i = 0; i < 128; ++i) {
        long double mid = (left + right) / 2.0;
        if (check(table, L, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return right;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long L, n;
    cin >> L >> n;
    vector<Interval> intrs;
    for (int i = 0; i < n; ++i) {
        long long t,v;
        cin >> t >> v;
        intrs.push_back({t,v});
    }
    long double ans = findMinL(intrs, L);
    cout <<  setprecision(20) << ans << '\n';
}
