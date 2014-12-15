#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<long long> ans;
long long n, p, q;

void gcd(long long a, long long b, long long &d, long long &x, long long &y) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    }
    else {
        gcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        ans.clear();
        cin >> n;
        for (int i = 2; i < n; i++) {
            if (n % i == 0) {
                p = i;
                q = n / i;
                break;
            }
        }
        ans.push_back(0);
        ans.push_back(1);
        long long d, x, y;
        gcd(p, q, d, x, y);
        x = ((x % q) + q) % q;
        y = (p * x - 1) / q;
        long long tmp = p * x;
        ans.push_back(tmp);
        gcd(q, p, d, x, y);
        x = ((x % p) + p) % p;
        tmp = q * x;
        ans.push_back(tmp);
        sort(ans.begin(), ans.end());
        int m = unique(ans.begin(), ans.end()) - ans.begin();
        for (int i = 0; i < m; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
