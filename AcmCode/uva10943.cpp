#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 105;


int dp[MAX_NUMBER][MAX_NUMBER];
int n, k;

int main() {

    while (scanf("%d%d", &n, &k) != EOF) {
        memset(dp, 0, sizeof(dp));
        if (!n && !k) {
            break;
        }
        for (int i = 0; i <= n; i++) {
            dp[1][i] = 1;
        }
        for (int i = 2; i <= k; i++) {
            for (int k = 0; k <= n; k++) {
                for (int s = 0; s <= k; s++) {
                    dp[i][k] = (dp[i][k] + dp[i - 1][s]) % 1000000;
                }
            }
        }
        printf("%d\n", dp[k][n]);
    }
    return 0;
}
