#include <iostream>
#include <stdio.h>
using namespace std;

void extended_eculid(long long a, long long b, long long *gcd_d, long long *x, long long *y) {
    if (b == 0) {
        *gcd_d = a;
        *x = 1;
        *y = 0;
    }
    else {
        extended_eculid(b, a % b, gcd_d, x, y);
        long long temp_x = *x;
        long long temp_y = *y;
        *x = temp_y;
        *y = temp_x - (a / b) * temp_y;
    }
}

int main() {

    long long x, y, m, n, L;
    long long a, b, gcd_d, x_0, y_0, ans;
    while (scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L) != EOF) {
        a = m - n;
        b = y - x;
        /*        if (a < 0) {
            a = -a;
            b = -b;
            }*/
        extended_eculid(a, L, &gcd_d, &x_0, &y_0);
        if ((b % gcd_d) != 0) {
            cout << "Impossible" << endl;
        }
        else {
            ans = (x_0 * b / gcd_d) % L;
            ans = (ans + L) % (L / gcd_d);
            if (ans == 0) {
                ans += L;
            }
            cout << ans << endl;
        }
    }
    return 0;
}
