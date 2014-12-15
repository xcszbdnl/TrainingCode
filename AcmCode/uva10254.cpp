#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 10005;

long long value[MAX_NUMBER + 10];


int main() {

    value[0] = 0;
    value[1] = 1;
    value[2] = 3;
    for (int i = 3; i < MAX_NUMBER; i++) {
        int k;
        if (i > 50) {
            k = i - 50;
        }
        else {
            k = 0;
        }
        long long ans = -1;
        for (; k < i; k++) {
            long long temp = 2 * value[k] + (1ll << (i - k)) - 1;
            if (ans == -1 || temp < ans) {
                ans = temp;
            }
        }
        value[i] = ans;
    }
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("%lld\n", value[n]);
    }
    return 0;
}
