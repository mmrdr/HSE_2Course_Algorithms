#include <iostream>
#include <set>
using namespace std;
int main() {
    int n;
    cin >> n;
    set<string> set;
    int* arr = new int[n];
    for (size_t i = 0; i < n; ++i) {
        int el;
        cin >> el;
        arr[i] = el;
    }
    int max = -1;
    int ans;
    for (size_t i = n - 1; i != -1; --i) {
        int cnt = 0;
        string str;
        for (size_t j = 0; j < n; ++j) {
            str += to_string(arr[(j+i)%n]);
            if (arr[j] != arr[(j + i) % n]) {
                ++cnt;
            }
        }
        if (cnt > max) {
            max = cnt;
            ans = 1;
            set.insert(str);
        } else if (cnt == max) {
            if (set.find(str) == set.end()) {
                set.insert(str);
                ++ans;
            }
        }
    }
    cout << ans << "\n";
    delete[] arr;
}