#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    int left;
    int right;
    size_t length() const {
        if (left > right) {
            return 0;
        }
        return right - left + 1;
    }
    Interval overlap(const Interval& other) {
        if (other.left > right || left > other.right) {
            return {1, 0};
        }
        int new_left = left > other.left ? left : other.left;
        int new_right = right < other.right ? right : other.right;
        return {new_left, new_right};
    }
};

void merge(std::vector<Interval>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Interval> L(n1), R(n2);

    std::copy(arr.begin() + left, arr.begin() + left + n1, L.begin());
    std::copy(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2, R.begin());

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i].right < R[j].right || (L[i].right == R[j].right && L[i].left > R[j].left)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Interval>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    size_t n;
    std::cin >> n;
    if (n == 0) {
        std::cout << 0;
        return 0;
    }
    std::vector<Interval> intervals(n);
    for (size_t i = 0; i < n; ++i) {
        int r, l;
        std::cin >> l >> r;
        intervals[i] = {l, r};
    }
    mergeSort(intervals, 0, intervals.size() - 1);

    Interval large_interval = {0, 0};
    size_t ans = 0;
    Interval current = intervals[0];
    for (size_t i = 0; i < n - 1; ++i) {
        Interval overlap = current.overlap(intervals[i + 1]);
        if (overlap.length() > ans) {
            ans = overlap.length();
            large_interval = overlap;
        }
        if (intervals[i + 1].right > current.right) {
            current = intervals[i + 1];
        }
    }

    if (ans) {
        std::cout << ans << std::endl;
        std::cout << large_interval.left << " " << large_interval.right;
    } else {
        std::cout << 0;
    }
    return 0;
}