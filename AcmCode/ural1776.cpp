#include <cstdio>
#include <cstring>

#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_NUMBER = 406;

double dp[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER][MAX_NUMBER];
int n;

void dfs(int i, int j) {
    if (vis[i][j]) {
        return ;
    }
    vis[i][j] = 1;
    if (i == j) {
        dp[i][j] = 10;
        return ;
    }
    else {
        int times = j - i + 1;
        dfs(i + 1, j);
        dp[i][j] = dp[i][j] + (10 + dp[i + 1][j]) * 1.0 / times;
        dfs(i, j - 1);
        dp[i][j] = dp[i][j] + (10 + dp[i][j - 1]) * 1.0 / times;
        for (int k = i + 1; k <= j - 1; k++) {
            dfs(k + 1, j);
            dfs(i, k - 1);
            double max_number = max(dp[k + 1][j], dp[i][k - 1]);
            dp[i][j] = dp[i][j] + (max_number + 10) * 1.0 / times;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    memset(vis, 0, sizeof(vis));
    memset(dp, 0, sizeof(dp));
    dfs(2, n - 1);
    printf("%.11lf\n", dp[2][n - 1]);
}
