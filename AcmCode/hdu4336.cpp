#include <cstdio>
#include <cstring>
#include <cmath>
const int maxn = 20;
const double eps = 1e-8;
double p[maxn + 7];

double dp[(1 << maxn) + 7];
int vis[(1 << maxn) + 7];
int n;
void dfs(int cnt) {
    if (vis[cnt]) {
        return ;
    }
    vis[cnt] = 1;
    dp[cnt] = 0;
    double cnt_p = 0;
    double result = 0;
    for (int i = 0; i < n; i++) {
        if (cnt & (1 << i)) {
            continue;
        }
        dfs(cnt | (1 << i));
        result  += p[i] * (dp[cnt | (1 << i)] + 1);
        cnt_p += p[i];
    }
    dp[cnt] = (result + (1 - cnt_p)) / cnt_p;
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < (1 << n); i++) {
            vis[i] = 0;
        }
        dp[(1 << n) - 1] = 0;
        vis[(1 << n) - 1] = 1;
        int flag = 0;
        for (int i = 0; i < n; i++) {
            scanf("%lf", &p[i]);
            if (fabs(p[i] - 1.0) < eps) {
                flag = 1;
            }
        }
        if (!flag) {
            for (int i = (1 << n) - 2; i >= 0; i--) {
                dp[i] = 0;
                double cnt_p = 0;
                double result = 0;
                for (int j = 0; j < n; j++) {
                    if (!(i & (1 << j))) {
                        cnt_p += p[j];
                        result += p[j] * (dp[i | (1 <<j)] + 1);
                    }
                }
                dp[i] = (result + (1 - cnt_p)) / cnt_p;
            }
//            dfs(0);
        }
        else {
            printf("0.0\n");
            continue;
        }
        printf("%.5f\n", dp[0]);
    }
    return 0;
}
