#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 50;
long long ans[MAX_NUMBER];


int main() {
    ans[0] = 1;
    ans[2] = 3;
    for (int i = 4; i <= 60; i++) {
        ans[i] = 3 * ans[i - 2];
        for (int k = i - 4; k >= 0; k -= 2) {
            ans[i] += 2 * ans[k];
        }
    }
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n < 0) {
            break;
        }
        if (n % 2) {
            printf("0\n");
        }
        else {
            printf("%lld\n", ans[n]);
        }
    }
    return 0;
}
