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

void quickSortHybrid(vector<int>& arr, int lower, int higher, int limit) {
    if (lower < higher) {
        if (higher - lower < 16) {
            insertionSort(arr, lower, higher);
        } else if (limit <= 0) {
            make_heap(arr.begin() + lower, arr.begin() + higher + 1);
            sort_heap(arr.begin() + lower, arr.begin() + higher + 1);
        } else {
            int ind = partition(arr, lower, higher);
            quickSortHybrid(arr, lower, ind - 1, limit - 1);
            quickSortHybrid(arr, ind + 1, higher, limit - 1);
        }
    }
}


void quickSort(std::vector<int>& nums, int left, int right) {
    if (left < right) {
        int ind = partition(nums, left, right);
        quickSort(nums, left, ind - 1);
        quickSort(nums, ind + 1, right);
    }
}


/*
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
    quickSortHybrid(arr, 0, n - 1, limit);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
}
*/

