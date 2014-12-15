#include <cstdio>
#include <cstring>

const int maxn = 50;

long long dp[maxn][maxn][maxn];
int vis[maxn][maxn][maxn];
void dfs(int left, int right, int h) {
    if (right < left) {
        if (h == 0) {
            dp[left][right][0] = 1;
        }
        else {
            dp[left][right][0] = 0;
        }
        return ;
    }
    if (vis[left][right][h]) {
        return ;
    }
    vis[left][right][h] = 1;
    dp[left][right][h] = 0;
    for (int i = left; i <= right; i++) {
        if (h == 0) {
            dfs(left, i - 1, 0);
            dfs(i + 1, right, 0);
            dp[left][right][h] += dp[left][i - 1][0] * dp[i + 1][right][0];
        }
        else {
            dfs(left, i - 1, h - 1);
            dfs(i + 1, right, 0);
            dp[left][right][h] += dp[left][i - 1][h - 1] * dp[i + 1][right][0];
            dfs(left, i - 1, 0);
            dfs(i + 1, right, h - 1);
            dp[left][right][h] += dp[left][i - 1][0] * dp[i + 1][right][h - 1];
            dp[left][right][h] -= dp[left][i - 1][h - 1] * dp[i + 1][right][h - 1];
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    int n, h;
    scanf("%d%d", &n, &h);
    memset(vis, 0, sizeof(vis));
    dfs(1, n, h);
    printf("%I64d\n", dp[1][n][h]);
    return 0;
}
