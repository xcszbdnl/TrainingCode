#include <cstdio>
#include <cstring>
#include <cmath>

const int maxn = 100007;
double dp[maxn], p[maxn];
int n, m;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &m, &n);
    dp[0] = 0;
    double ans = 0;
    for (int i = 1; i <= m; i++) {
        dp[i] = pow((i * 1.0 / m), n);
        p[i] = dp[i] - dp[i - 1];
        ans += p[i] * i;
    }
    printf("%.7f\n", ans);
    return 0;
}
