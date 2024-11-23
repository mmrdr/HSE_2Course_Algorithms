#include <iostream>
#include <vector>
using namespace std;

void sinkDown(int k, int N, vector<int>& heap) {
    while(2 * k <= N) {
        int j = 2 * k;
        if (j < N && heap[j] < heap[j + 1]) ++j;
        if (heap[k] >= heap[j]) break;
        std::swap(heap[k], heap[j]);
        k = j;
    }
}

void swipUp(int k, int N, vector<int>& heap) {
    while(k > 1 && heap[k / 2] < heap[k]) {
        swap(heap[k / 2], heap[k]);
        k = k / 2;
    }
}

void heapify(vector<int>& heap, int k, int N) {
    sinkDown(k, N, heap);
}

void buildMaxHeap(vector<int>& heap) {
    int N = heap.size() - 1;
    for (int k =  N / 2; k >= 1; --k) {
        heapify(heap, k, N);
    }
}

void heapSort(vector<int>& heap) {
    int N = heap.size() - 1;
    int n_ans = N;
    vector<int> ans;
    buildMaxHeap(heap);

    while(N > 1) {
        ans.push_back(heap[1]);
        swap(heap[1], heap[N]);
        --N;
        heapify(heap, 1, N);
    }
    ans.push_back(heap[1]);
    for (int i = n_ans - 1; i >= 0; --i) {
        cout << ans[i] << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> heap(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        int el;
        cin >> el;
        heap[i] = el;
    }
    heapSort(heap);
}
