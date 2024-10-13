#include <iostream>
#include <string>
using namespace std;

string multiply(const string& x, const string& y) {
    int a = x.size();
    int b = y.size();
    string ans = string(a + b, '0');
    for (int i = a - 1; i >= 0; --i) {
        int add = 0;
        for (int j = b - 1; j >= 0; --j) {
            int mul = (ans[i + j + 1] - '0') + (x[i] - '0') * (y[j] - '0') + add;
            ans[i + j + 1] = (mul % 10) + '0';
            add = mul / 10;
        }
        ans[i] += add;
    }
    size_t start = ans.find_first_not_of('0');
    if (start == string::npos) return "0";
    return ans.substr(start);
}

string sum(const string& x, const string& y) {
    int add = 0;
    int i = x.size() - 1;
    int j = y.size() - 1;
    int maxNumber = max(x.size(), y.size());
    string res(maxNumber + 1, '0');
    int k = maxNumber;
    while(i >= 0 || j >= 0 || add) {
        int sum = add;
        if (i >= 0) {
            sum += x[i] - '0';
            --i;
        }
        if (j >= 0) {
            sum += y[j] - '0';
            --j;
        }
        add = sum / 10;
        res[k] = (sum % 10) + '0';
        --k;
    }
    size_t start = res.find_first_not_of('0');
    if (start == string::npos) return "0";
    return res.substr(start);
}

string subtract(const string& x, const string& y) {
    int add = 0;
    int i = x.size() - 1;
    int j = y.size() - 1;
    string res(x.size(), '0');
    int k = x.size() - 1;
    while(i >= 0) {
        int diff = (x[i] - '0') - add;
        if (j >= 0) {
            diff -= (y[j] - '0');
            --j;
        }
        if (diff < 0) {
            diff += 10;
            add = 1;
        } else {
            add = 0;
        }
        res[k] = diff + '0';
        --i;
        --k;
    }
    size_t start = res.find_first_not_of('0');
    if (start == string::npos) return "0";
    return res.substr(start);
}

string karatsuba(const string& x, const string& y) {
    string a = x;
    string b = y;
    if (a.size() == 0 || b.size() == 0) {
        return "0";
    }
    if (a.size() < 10 && b.size() < 10) {
        return multiply(a,b);
    }
    while(a.size() < b.size()) {
        a = '0' + a;
    }
    while(a.size() > b.size()) {
        b = '0' + b;
    }
    int n = a.size();
    if (n <= 1) {
        return to_string((a[0] - '0') * (b[0] - '0'));
    }
    int mid = n / 2;
    string a1 = a.substr(0, a.size() - mid);
    string a0 = a.substr(a.size() - mid);
    string b1 = b.substr(0, b.size() - mid);
    string b0 = b.substr(b.size() - mid);

    string a1b1 = karatsuba(a1, b1);
    string a0b0 = karatsuba(a0, b0);
    string a1a0b1b0 = karatsuba(sum(a1,a0), sum(b1,b0));
    string diff = subtract(a1a0b1b0, sum(a1b1, a0b0));
    string ans = sum(a1b1 + string(2 * mid, '0'), diff + string(mid, '0'));
    ans = sum(ans, a0b0);
    size_t start = ans.find_first_not_of('0');
    if (start == string::npos) return "0";
    return ans.substr(start);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string str1;
    cin >> str1;
    string str2;
    cin >> str2;
    string res = karatsuba(str1, str2);
    cout << res;
}
