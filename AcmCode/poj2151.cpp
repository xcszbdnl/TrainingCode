#include <cstdio>
#include <cstring>

const int maxn = 1007;

double least_1[maxn];
double least_n[maxn];
double p[maxn][maxn];
double dp[maxn][32];
int m, t, n;
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d%d", &m, &t, &n) != EOF) {
        if (!m && !t && !n) {
            break;
        }
        memset(least_1, 0, sizeof(least_1));
        memset(least_n, 0, sizeof(least_n));
        for (int i = 1; i <= t; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%lf", &p[i][j]);
            }
        }
        for (int i = 1; i <= t; i++) {
            least_1[i] = 1;
            for (int j = 1; j <= m; j++) {
                least_1[i] *= (1 - p[i][j]);
            }
            least_1[i] = 1 - least_1[i];
        }
        for (int i = 1; i <= t; i++) {
            memset(dp, 0, sizeof(dp));
            dp[0][0] = 1;
            for (int j = 1; j <= m; j++) {
                dp[j][0] = dp[j - 1][0] * (1 - p[i][j]);
                for (int k = 1; k <= j; k++) {
                    dp[j][k] += dp[j - 1][k - 1] * p[i][j];
                    dp[j][k] += dp[j - 1][k] * (1 - p[i][j]);
                }
            }
            for (int j = n; j <= m; j++) {
                least_n[i] += dp[m][j];
            }
        }
//        for (int i = 1; i <= t; i++) {
//            printf("1:%.3f--->n:%.3f\n", least_1[i], least_n[i]);
//        }
//        double ans = 0;
//        double temp = 1;
//        for (int i = 1; i <= t; i++) {
//            ans += (1 - least_1[i]);
//            temp = temp * (least_1[i] - least_n[i]);
//        }
//        printf("%f,%f\n", ans, temp);
        double p1 = 1;
        double p2 = 1;
        for (int i = 1; i <= t; i++) {
            p1 *= least_1[i];
            p2 *= (least_1[i] - least_n[i]);
        }
//        ans += temp;
//        ans = 1 - ans;
        printf("%.3f\n", p1 - p2);
    }
    return 0;
}
