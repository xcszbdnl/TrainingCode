#include <cstdio>
#include <cstring>

const int maxn = 1007;

long long dp[100][maxn];
int n, sums;
int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &sums);
    if (sums % 2) {
        printf("0\n");
        return 0;
    }
    sums /= 2;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = sums; j >= 0; j--) {
            for (int k = 0; k <= 9 && k <= j; k++) {
                dp[i][j] += dp[i - 1][j - k];
            }
        }
    }
    long long ans = dp[n][sums];
    ans *= ans;
    printf("%I64d\n", ans);
    return 0;
}
