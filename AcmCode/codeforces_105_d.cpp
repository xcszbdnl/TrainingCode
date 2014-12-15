#include <cstdio>
#include <cstring>

const int maxn = 1007;

double dp[maxn][maxn];
int n, m;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= m; i++) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] += i * 1.0 / (i + j);
            if (j >= 2) {
                dp[i][j] += (j * 1.0 / (i + j) * (j - 1) / (i + j - 1) * i * 1.0 / (i + j - 2)) * dp[i - 1][j - 2];
            }
            if (j >= 3) {
                dp[i][j] += (j * 1.0 / (i + j) * (j - 1) / (i + j - 1) * (j - 2) / (i + j - 2)) * dp[i][j - 3];
            }
        }
    }
    printf("%.9f\n", dp[n][m]);
    return 0;
}
