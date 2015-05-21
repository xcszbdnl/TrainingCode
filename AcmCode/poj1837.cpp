#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 20000;

long long dp[2][maxn * 2 + maxn];
int loc[maxn];
int c, g;
int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d%d", &c, &g) != EOF) {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= c; i++) {
      scanf("%d", &loc[i]);
    }
    int flag = 0;
    dp[1][maxn] = 1;
    for (int i = 1; i <= g; i++) {
      int a;
      scanf("%d", &a);
      for (int j = 0; j < maxn * 2; j++) {
        dp[flag][j] = 0;
        for (int k = 1; k <= c; k++) {
          if (j - a * loc[k] >= 0) {
            dp[flag][j] += dp[flag ^ 1][j - a * loc[k]];
          }
        }
      }
      flag = flag ^ 1;
    }
    flag ^= 1;
    printf("%I64d\n", dp[flag][maxn]);
  }
  return 0;
}
