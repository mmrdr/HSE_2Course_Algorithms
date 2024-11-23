#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

void radixSort(vector<int>& arr) {
    int max = 0;
    vector<queue<int>> qs(520);
    for (int el : arr) {
        if (max < to_string(el).size()) max = to_string(el).size();
    }
    for (int i = 0; i < max; ++i) {
        for (int j = 0; j < arr.size(); ++j) {
            int dgt = (arr[j] / static_cast<int>(pow(256, i))) % 256;
            qs[dgt + 256].push(arr[j]);
        }
        int ind = 0;
        for (int k = 0; k < 520; ++k) {
            while (!qs[k].empty()) {
                arr[ind++] = qs[k].front();
                qs[k].pop();
            }
        }
    }
}



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        int el;
        cin >> el;
        nums[i] = el;
    }
    radixSort(nums);
    for (int el : nums) {
        cout << el << " ";
    }
}
