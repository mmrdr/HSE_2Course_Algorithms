#include <iostream>
#include <vector>
using namespace std;

struct Dbl {
    int numerator, denominator;

    bool operator==(const Dbl& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator<(const Dbl& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator<=(const Dbl& other) const {
        return numerator * other.denominator <= other.numerator * denominator;
    }
};

void stableMerge(vector<Dbl>& arr, int left, int mid, int right) {
    vector<Dbl> left_dbl(arr.begin() + left, arr.begin() + mid + 1);
    vector<Dbl> right_dbl(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0;
    int j = 0;
    int k = left;
    while(i < left_dbl.size() && j < right_dbl.size()) {
        if (left_dbl[i] <= right_dbl[j]) {
            arr[k++] = left_dbl[i++];
        } else {
            arr[k++] = right_dbl[j++];
        }
    }
    while(i < left_dbl.size()) {
        arr[k++] = left_dbl[i++];
    }
    while(j < right_dbl.size()) {
        arr[k++] = right_dbl[j++];
    }
}

void stableMergeSort(vector<Dbl>& arr, int left, int right)  {
    if (left < right) {
        int mid = left + (right - left) / 2;
        stableMergeSort(arr, left, mid);
        stableMergeSort(arr, mid + 1, right);
        stableMerge(arr, left, mid, right);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Dbl> arr(n);
    for (int i = 0; i < n; ++i) {
        string input;
        cin >> input;
        size_t s = input.find('/');
        int numerator = stoi(input.substr(0, s));
        int denominator = stoi(input.substr(s + 1));
        arr[i] = {numerator, denominator};
    }
    stableMergeSort(arr, 0, arr.size() - 1);
    for (auto el : arr){
        cout << el.numerator << '/' << el.denominator << " ";
    }
}
