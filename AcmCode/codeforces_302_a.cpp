#include <cstdio>
#include <cstring>

const int maxn = 607;

long long dp[2][maxn][maxn];
int a[maxn];
int n, m, b, mod;
int main() {

  scanf("%d%d%d%d", &n, &m, &b, &mod);
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  dp[0][0][0] = 1;
  int flag = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k <= b; k++) {
        dp[flag][j][k] = dp[flag ^ 1][j][k];
        if (j >= 1 && k >= a[i]) {
          dp[flag][j][k] = (dp[flag][j][k] + dp[flag][j - 1][k - a[i]]) % mod;
        }
      }
    }
    flag ^= 1;
  }
  long long ans = 0;
  for (int i = 0; i <= b; i++) {
    ans = (ans + dp[flag ^ 1][m][i]) % mod;
  }
  printf("%I64d\n", ans);
  return 0;
}
