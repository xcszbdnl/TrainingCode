#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 210007;
const int temp = 100000;
const int INF = 10000007;
int dp[2][maxn];
int v, n;
int cost[maxn], value[maxn];
int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d", &n) != EOF) {
    int flag = 0;
    v = temp;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &cost[i], &value[i]);
      if (cost[i] > 0) {
        v += cost[i];
      }
      else {
        v -= cost[i];
      }
    }
    for (int i = 0; i < maxn; i++) {
      dp[0][i] = -INF;
      dp[1][i] = -INF;
    }
    dp[flag ^ 1][temp] = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= v; j++) {
        dp[flag][j] = dp[flag ^ 1][j];
        if (j - cost[i] >= 0 && dp[flag ^ 1][j - cost[i]] != -INF) {
          dp[flag][j] = max(dp[flag][j], dp[flag ^ 1][j - cost[i]] + value[i]);
        }
      }
      flag = flag ^ 1;
    }
    int ans = -temp;
    flag ^= 1;
    for (int j = temp; j <= v; j++) {
      if (dp[flag][j] >= 0) {
        ans = max(ans, j - temp + dp[flag][j]);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
