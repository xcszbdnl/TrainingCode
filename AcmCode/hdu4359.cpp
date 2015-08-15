#include <cstdio>
#include <cstring>

const int maxn = 500;

long long mod = 1e9 + 7;

long long dp[maxn][maxn];
long long c[maxn][maxn];
int vis[maxn][maxn];
int n, d;

void init() {
    c[0][0] = 1;
    for (int i = 1; i < maxn; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
        }
    }
}
void dfs(int cnt_n, int depth) {
    if (vis[cnt_n][depth] != -1) {
        return ;
    }
    vis[cnt_n][depth] = 1;
    if (depth == 0) {
        if (cnt_n == 0) {
            dp[cnt_n][depth] = 1;
        }
        else {
            dp[cnt_n][depth] = 0;
        }
        return ;
    }
    if (cnt_n == 0) {
        dp[cnt_n][depth] = 0;
        return ;
    }
    if (cnt_n == 1) {
        if (depth == 0) {
            dp[cnt_n][depth] = 0;
        }
        else {
            dp[cnt_n][depth] = 1;
        }
        return ;
    }
    dfs(cnt_n - 1, depth - 1);
    dp[cnt_n][depth] = (2 * cnt_n * dp[cnt_n - 1][depth - 1]) % mod;
    for (int i = 1; i <= cnt_n - 2; i++) {
        dfs(i, depth - 1);
        dfs(cnt_n - 1 - i, depth - 1);
        long long tmp = (c[cnt_n][1] * c[cnt_n - 2][i]) % mod;
        tmp = (tmp * dp[i][depth - 1]) % mod;
        tmp = (tmp * dp[cnt_n - 1 - i][depth - 1]) % mod;
        dp[cnt_n][depth] = (dp[cnt_n][depth] + tmp) % mod;
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    init();
    memset(vis, -1, sizeof(vis));
    int test_case;
    scanf("%d", &test_case);
    int ncase = 1;
    while (test_case--) {
        printf("Case #%d: ", ncase++);
        scanf("%d%d", &n, &d);
        dfs(n, d);
        dfs(n, d - 1);
        long long ans = dp[n][d] - dp[n][d - 1];
//        printf("dp:%I64d-->%I64d\n", dp[n][d], dp[n][d - 1]);
        ans = ((ans % mod) + mod) % mod;
        printf("%I64d\n", ans);
    }
    return 0;
}
