#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

double estimate(vector<int>& spots) {
    size_t n = spots.size();
    vector<int> setd1(2 * n - 1);
    vector<int> setd2(2 * n - 1);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int d1 = i + spots[i];
        int d2 = i - spots[i] + (n-1);
        if (!setd1[d1] && !setd2[d2]) {
            cnt++;
            setd1[d1] = 1;
            setd2[d2] = 1;
        }
    }
    return cnt;
}

std::vector<int> solve(int n) {
    std::mt19937 generator(45);
    std::uniform_int_distribution<> distr(0, n - 1);
    std::uniform_real_distribution<> real_distr(0, n - 1);
    vector<int> spots(n);
    for (int i = 0; i < n; ++i) {
        spots[i] = i;
    }
    shuffle(spots.begin(), spots.end(), generator);
    double energy = estimate(spots);
    double Ti = 1.0;
    while(energy < n) {
        Ti *= 0.99;
        vector<int> newSpots = spots;
        swap(newSpots[distr(generator)], newSpots[distr(generator)]);
        double newEnergy = estimate(newSpots);
        double dE = newEnergy - energy;
        if (newEnergy > energy || real_distr(generator) < exp(dE / Ti)) {
            spots = newSpots;
            energy = newEnergy;
        }
    }
    return spots;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> ans = solve(n);
    for (auto el : ans) {
        cout << el + 1 << " ";
    }
}
