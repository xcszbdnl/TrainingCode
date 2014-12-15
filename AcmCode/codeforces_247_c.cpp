#include <cstdio>
#include <cstring>

const int maxn = 107;
const long long mod = 1e9 + 7;
long long dp[maxn], vis[maxn];
int n, k, d;

void dfs(int s, int max_num) {
    if (dp[s] != -1) {
        return ;
    }
    if (s == 1 || s == 0) {
        if (max_num < s) {
            dp[s] = 0;
        }
        else {
            dp[s] = 1;
        }
        return ;
    }
    dp[s] = 0;
    for (int i = 1; i <= s && i <= max_num; i++) {
        dfs(s - i, max_num);
        dp[s] = (dp[s] + dp[s - i]) % mod;
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &k, &d);
    memset(dp, -1, sizeof(dp));
    dfs(n, k);
    long long ans = dp[n];
    memset(dp, -1, sizeof(dp));
    dfs(n, d - 1);
    ans = (ans - dp[n]) % mod;
    ans += mod;
    ans %= mod;
    printf("%I64d\n", ans);
    return 0;
}
