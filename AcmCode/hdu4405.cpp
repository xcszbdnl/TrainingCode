#include <cstdio>
#include <cstring>

const int maxn = 100007;

double dp[maxn];
int next[maxn];
int n, m;
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        if (!n && !m) {
            break;
        }
        memset(next, -1, sizeof(next));
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            next[a] = b;
        }
        for (int i = n - 1; i >= 0; i--) {
            if (next[i] != -1) {
                dp[i] = dp[next[i]];
            }
            else {
                for (int k = 1; k <= 6; k++) {
                    dp[i] += (dp[i + k] + 1) * 1.0 / 6;
                }
            }
        }
        printf("%.4f\n", dp[0]);
    }
    return 0;
}
