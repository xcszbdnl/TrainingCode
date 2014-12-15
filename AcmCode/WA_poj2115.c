#include <stdio.h>
#include <cmath>

void extended_eculid(long long a, long long b, long long *d, long long *x, long long *y) {
    long long temp_x, temp_y;
    if (b == 0) {
        *d = a;
        *x = 1;
        *y = 0;
    }
    else {
        extended_eculid(b, a % b, d, x, y);
        temp_x = *x;
        temp_y = *y;
        *x = temp_y;
        *y = (temp_x - (a / b) * temp_y);
    }
}

int main() {

    long long A, B, C, K;
    long long gcd_d, x_0, y_0, ans_x;
    long long power_k;
    while (scanf("%ld%ld%ld%ld", &A, &B, &C, &K) != EOF) {
        if (!A && !B && !C && !K) {
            break;
        }
        power_k = (long long)pow(2.0, (int)K);
        extended_eculid(C, power_k, &gcd_d, &x_0, &y_0);
        if ((B - A) % gcd_d != 0) {
            printf("FOREVER\n");
        }
        else {
            ans_x = (x_0 * (B - A) / gcd_d) % power_k;
            ans_x = (ans_x + power_k) % (power_k / gcd_d);
            printf("%ld\n", ans_x);            
        }
    }
    return 0;
}
