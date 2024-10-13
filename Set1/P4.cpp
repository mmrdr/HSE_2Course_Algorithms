#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    stack<int> st;
    vector<pair<int, int>> acts;
    int bn = 1;
    for (int i = 0; i < N; ++i) {
        int n;
        cin >> n;
        while (!st.empty() && st.top() == bn) {
            acts.push_back({2, 1});
            st.pop();
            bn++;
        }
        st.push(n);
        acts.push_back({1, 1});
        while (!st.empty() && st.top() == bn) {
            acts.push_back({2, 1});
            st.pop();
            bn++;
        }
    }
    while (!st.empty()) {
        if (st.top() == bn) {
            acts.push_back({2, 1});
            st.pop();
            bn++;
        } else {
            cout << 0 << endl;
            return 0;
        }
    }
    vector<pair<int, int>> arr;
    for (auto& act : acts) {
        if (arr.empty() || arr.back().first != act.first) {
            arr.push_back(act);
        } else {
            arr.back().second += act.second;
        }
    }
    for (auto& act : arr) {
        cout << act.first << " " << act.second << endl;
    }
}