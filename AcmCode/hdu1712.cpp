#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 106;
int a[maxn][maxn];
int dp[2][maxn];
int n, m;
int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d%d", &n, &m) != EOF) {
    if (m + n == 0) {
      break;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &a[i][j]);
      }
    }
    memset(dp, 0, sizeof(dp));
    int flag = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        dp[flag][j] = dp[flag ^ 1][j];
        for (int k = 1; k <= j; k++) {
          dp[flag][j] = max(dp[flag][j], dp[flag ^ 1][j - k] + a[i][k]);
        }
      }
      flag ^= 1;
    }
    flag ^= 1;
    printf("%d\n", dp[flag][m]);
  }
  return 0;
}
