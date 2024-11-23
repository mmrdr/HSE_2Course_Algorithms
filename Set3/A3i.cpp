#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while(j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int partition(vector<int>& arr, int low, int high) {
    int p = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] <= p) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int lower, int higher, int limit) {
    if (lower < higher) {
        if (higher - lower < 16) {
            insertionSort(arr, lower, higher);
        } else if (limit <= 0) {
            make_heap(arr.begin() + lower, arr.begin() + higher + 1);
            sort_heap(arr.begin() + lower, arr.begin() + higher + 1);
        } else {
            int ind = partition(arr, lower, higher);
            quickSort(arr, lower, ind - 1, limit - 1);
            quickSort(arr, ind + 1, higher, limit - 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    int limit = 2 * log2(n);
    quickSort(arr, 0, n - 1, limit);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
}
