#include <cstdio>
#include <cstring>
#include <cmath>
const int maxn = 1007;
double p[maxn][maxn][5];
double dp[maxn][maxn];
const double eps = 1e-8;
int n, m;
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 1; k <= 3; k++) {
                    scanf("%lf", &p[i][j][k]);
                }
            }
        }
        for (int i = n; i >= 1; i--) {
            for (int j = m; j >= 1; j--) {
                if (i == n && j == m) {
                    dp[i][j] = 0;
                }
                else {
                    if (fabs(p[i][j][1] - 1.0) < eps) {
                        dp[i][j] = 0;
                    }
                    else {
                        dp[i][j] = (p[i][j][2] * dp[i][j + 1] + p[i][j][3] * dp[i + 1][j] + 2)/ (1 - p[i][j][1]);
                    }
                }
            }
        }
        printf("%.3f\n", dp[1][1]);
    }
    return 0;
}
