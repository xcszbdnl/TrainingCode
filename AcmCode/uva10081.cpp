#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 105;

double dp[MAX_NUMBER][20];
int n, k;

int main() {

    while (scanf("%d%d", &k, &n) != EOF) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= k; i++) {
            dp[1][i] = 100.0 / (k + 1);
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (j == 0) {
                    dp[i][j] = (dp[i - 1][j] + dp[i - 1][j + 1]) / (k + 1);
                }
                else if (j == k) {
                    dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) / (k + 1);
                }
                else {
                    dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] + dp[i - 1][j + 1]) / (k + 1);
                }
            }
        }
        double ans = 0;
        for (int i = 0; i <= k; i++) {
            ans += dp[n][i];
        }
        printf("%.5lf\n", ans);
    }
    return 0;
}
