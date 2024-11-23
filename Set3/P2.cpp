#include <iostream>
#include <vector>
#include <string>
using namespace std;

void countingSort(vector<int>& arr) {
    vector<int> ans(21000000, 0);
    for (auto el: arr) {
        if (el < 0) {
            ++ans[el + 21000000];
        } else {
            ++ans[el];
        }
    }
    for (int i = 10000001; i <= 21000000; ++i) {
        if (ans[i] > 0) {
            for (int j = 0; j < ans[i]; ++j) {
                cout << i - 21000000 << " ";
            }
        }
    }
    for (int i = 0; i < 10000001; ++i ) {
        if (ans[i] > 0) {
            for (int j = 0; j < ans[i]; ++j) {
                cout << i << " ";
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        int el;
        cin >> el;
        arr[i] = el;
    }
    countingSort(arr);
}