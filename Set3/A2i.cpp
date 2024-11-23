#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int lb = mid - left + 1;
    int rb = right - mid;
    vector<int> lefts(lb), rights(rb);
    for (int i = 0; i < lb; ++i) {
        lefts[i] = arr[left + i];
    }
    for (int j = 0; j < rb; ++j) {
        rights[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < lb && j < rb) {
        if (lefts[i] <= rights[j]) {
            arr[k++] = lefts[i++];
        } else {
            arr[k++] = rights[j++];
        }
    }
    while(i < lb) {
        arr[k++] = lefts[i++];
    }
    while(j < rb) {
        arr[k++] = rights[j++];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortHybrid(vector<int>& arr, int left, int right) {
    if (right - left <= 15) {
        insertionSort(arr, left, right);
    } else {
        int mid = left + (right - left) / 2;
        mergeSortHybrid(arr, left, mid);
        mergeSortHybrid(arr, mid + 1, right);
        merge(arr, left, mid, right);
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
        int el;
        cin >> el;
        arr[i] = el;
    }
    mergeSort(arr, 0, arr.size() - 1);
    for (auto el : arr) {
        cout << el << " ";
    }
}
*/