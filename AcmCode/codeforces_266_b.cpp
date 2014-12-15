#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 500007;
long long n, a, b;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%I64d%I64d%I64d", &n, &a, &b);
    int swaped = 0;
    if (a < b) {
        swaped = 1;
        swap(a, b);
    }
    n = 6 * n;
    if (a * b >= n) {
        printf("%I64d\n", a * b);
        printf("%I64d %I64d\n", a, b);
        return 0;
    }
    int flag = 0;
    long long ans = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            long long x_1 = i;
            long long x_2 = n / i;
            if (x_1 < x_2) {
                swap(x_1, x_2);
            }
            if (x_1 >= a && x_2 >= b) {
                ans = x_1;
                flag = 1;
                break;
            }
        }
    }
    if (flag) {
        printf("%I64d\n", n);
        if (swaped) {
            ans = n / ans;
        }
        printf("%I64d %I64d\n", ans, n / ans);
    }
    else {
        long long tot;
        long long x_1, x_2;
        tot = (n / a + 1) * a;
        x_1 = a;
        x_2 = n / a + 1;
        long long tmp = (n / b + 1) * b;
        if (tmp < tot) {
            tot = tmp;
            x_1 = n / b + 1;
            x_2 = b;
        }
        printf("%I64d\n", tot);
        printf("%I64d %I64d\n", x_1, x_2);
    }
    return 0;
}

