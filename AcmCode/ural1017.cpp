#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 505;

long long f[MAX_NUMBER][MAX_NUMBER];


int main() {

    int n;
    scanf("%d", &n);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            for (int k = 0; k < j; k++) {
                f[i][j] += f[i - j][k];
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += f[n][i];
    }
    ans -= 1;
    printf("%I64d\n", ans);
    return 0;
}
