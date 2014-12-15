#include <cstdio>
#include <cstring>

const int maxn = 20007;
const int mod = 1000000000;
long long tree[maxn][22], val[maxn], dp[maxn][22];
int n;
int lowbit(int x) {
    return x & (-x);
}

long long sum(int x, int k) {
    long long ret = 0;
    while (x > 0) {
        ret = (tree[x][k] + ret) % mod;
        x -= lowbit(x);
    }
    return ret;
}

void add(int x, int k, long long value) {
    while (x <= n) {
        tree[x][k] += value;
        x += lowbit(x);
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    int k;
    scanf("%d%d", &n, &k);
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", &val[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            if (j == 2) {
                add(val[i], 1, 1);
            }
            long long temp = (sum(n, j - 1) - sum(val[i], j - 1));
            temp = ((temp % mod) + mod) % mod;
            dp[i][j] = (dp[i][j] + temp) % mod;
            add(val[i], j, dp[i][j]);
        }
    }
//    for (int i = 1; i <= n; i++) {
//        for (int j = 2; j <= k; j++) {
//            printf("%d ", dp[i][j]);
//        }
//        printf("\n");
//    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + dp[i][k]) % mod;
    }
    ans = ((ans % mod) + mod) % mod;
    printf("%I64d\n", ans);
    return 0;
}
