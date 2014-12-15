#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
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
    long long a, b, n;
    scanf("%I64d%I64d%I64d", &a, &b, &n);
    int flag = 0;
    if (a < b) {
        swap(a, b);
        flag = 1;
    }
    long long ans = -1;
    long long x_1, y_1;
    for (int i = 0; i <= min(n / a, b); i++) {
        long long c = n - a * i;
        long long y = (c / b) * b;
        long long tmp = a * i + y;
        if (tmp > ans) {
            ans = tmp;
            x_1 = i;
            y_1 = c / b;
        }
    }
    if (flag) {
        printf("%I64d %I64d\n", y_1, x_1);
    }
    else {
        printf("%I64d %I64d\n", x_1, y_1);
    }
    return 0;
}
