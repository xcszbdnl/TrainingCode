#include <cstdio>
#include <cstring>

const int maxn = 10007;


int n, m;
double dp[maxn];

int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d%d", &n, &m) != EOF) {
    if (n == 0 && m == 0) {
      break;
    }
    memset(dp, 0, sizeof(dp));
    dp[0] = 1.0;
    for (int i = 1; i <= n; i++) {
      dp[i] = 1e+50;
    }
    for (int i = 1; i <= m; i++) {
      int a;
      double b;
      scanf("%d%lf", &a, &b);
      for (int j = n; j >= a; j--) {
        double tmp = dp[j - a] * (1 - b);
        if (tmp < dp[j]) {
          dp[j] = tmp;
        }
      }
    }
    double ans = 1.0;
    for (int i = 0; i <= n; i++) {
      if (ans > dp[i]) {
        ans = dp[i];
      }
    }
    ans = 1 - ans;
    ans *= 100;
    printf("%.1lf%%\n", ans);
  }
  return 0;
}
