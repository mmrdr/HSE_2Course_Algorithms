#include <iostream>
#include <vector>
#include <random>
#include <bitset>
using namespace std;

vector<int> hexToBin(char hex) {
    int value;
    vector<int> r(4);
    value = hex <= '9' ? (hex - '0') : (hex - 'A' + 10);
    bitset<4> bin(value);
    int ind = 0;
    for (int i = 3; i >= 0; --i) {
        r[ind++] = static_cast<int>(bin[i]);
    }
    return r;
}

vector<vector<int>> readMatrix(int n) {
    vector<vector<int>> r(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        int ind = 0;
        for (int j = 0; j < (n + 3) / 4 ; ++j) {
            char c;
            cin >> c;
            vector<int> temp = hexToBin(c);
            for (int k = 0; k < temp.size() && k + 4 * j < n; ++k) {
                r[i][ind++] = temp[k];
            }
        }
    }
    return r;
}

vector<int> generateVectors(int n) {
    vector<int> r(n);
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<> distr(0,1);
    for (int i = 0; i < n; ++i) {
        r[i] = distr(generator);
    }
    return r;
}

vector<int> multiply(vector<vector<int>>& matrix, vector<int>& r) {
    int n = matrix.size();
    vector<int> result(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] = (result[i] + matrix[i][j] * r[j]) % 2;
        }
    }
    return result;
}

bool verify(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    vector<int> r = generateVectors(n);
    vector<int> Br = multiply(B, r);
    vector<int> X = multiply(A, Br);
    vector<int> Y = multiply(C, r);
    return X == Y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> A;
    vector<vector<int>> B;
    vector<vector<int>> C;
    A = readMatrix(n);
    B = readMatrix(n);
    C = readMatrix(n);
    bool f = true;
    for (int i = 0; i < 20; ++i) {
        f = verify(A,B,C);
        if (!f) break;
    }
    cout << (f ? "YES" : "NO");
}
