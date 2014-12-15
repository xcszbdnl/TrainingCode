#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 100;


long long dp[MAX_NUMBER][MAX_NUMBER];
int n, m, k;

int main() {

    while (scanf("%d%d%d", &n, &k, &m) != EOF) {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= m; i++) {
            dp[1][i] = 1;
        }
        for (int i = 2; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = j - 1; k >= 1 && j - k <= m; k--) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
        printf("%lld\n", dp[k][n]);
    }
    return 0;
}
