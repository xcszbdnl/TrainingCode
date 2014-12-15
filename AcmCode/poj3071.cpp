#include <cstdio>
#include <cstring>

const int maxn = 1000;
int n;

double p[maxn][maxn];
double dp[maxn][maxn];

void deal(int round, int left, int left_end, int right, int right_end) {
    for (int i = left; i <= left_end; i++) {
        dp[round][i] = 0;
        for (int j = right; j <= right_end; j++) {
            dp[round][i] += dp[round - 1][i] * dp[round - 1][j] * p[i][j];
        }
    }
    for (int i = right; i <= right_end; i++) {
        dp[round][i] = 0;
        for (int j = left; j <= left_end; j++) {
            dp[round][i] += dp[round - 1][i] * dp[round - 1][j] * p[i][j];
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        if (n == -1) {
            break;
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < (1 << n); i++) {
            for (int j = 0; j < (1 << n); j++) {
                scanf("%lf", &p[i][j]);
            }
        }
        for (int i = 0; i < (1 << n); i++) {
            dp[0][i] = 1.0;
        }
        for (int i = 1; i <= n; i++) {
            int people = 1 << (i - 1);
            for (int j = 0; j < (1 << n); j += (1 << i)) {
                deal(i, j, j + people - 1, j + people, j + people + people - 1);
            }
        }
        double max_ans;
        int loc = 0;
        max_ans = -1;
        for (int i = 0; i < (1 << n); i++) {
            if (dp[n][i] > max_ans) {
                max_ans = dp[n][i];
                loc = i + 1;
            }
        }
        printf("%d\n", loc);
    }
    return 0;
}
