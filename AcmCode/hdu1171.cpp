#include <cstdio>
#include <cstring>

const int maxn = 100;

int dp[53][150000];
int n;

int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d", &n) != EOF) {
    if (n < 0) {
      break;
    }
    int cnt_sums = 0;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      for (int j = 0; j <= cnt_sums; j++) {
        if (dp[i - 1][j]) {
          for (int k = 0; k <= b; k++) {
            dp[i][j + a * k] = 1;
          }
        }
      }
      cnt_sums += a * b;
    }
    int ans = 0;
    for (int i = cnt_sums / 2; i >= 0; i--) {
      if (dp[n][i]) {
        ans = i;
        break;
      }
    }
    printf("%d %d\n", cnt_sums - ans, ans);
  }
  return 0;
}
