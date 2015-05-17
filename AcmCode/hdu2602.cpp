#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10007;


int n, v;
int dp[maxn];
int cost[maxn], weight[maxn];
int main() {
  //freopen("in.txt", "r", stdin);
  int test_case;
  scanf("%d", &test_case);
  while (test_case--) {
    scanf("%d%d", &n, &v);
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
      scanf("%d", &weight[i]);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", &cost[i]);
    }
    for (int i = 1; i <= n; i++) {
      for (int j = v; j >= cost[i]; j--) {
        dp[j] = max(dp[j], dp[j - cost[i]] + weight[i]);
      }
    }
    int ans = 0;
    for (int i = 0; i <= v; i++) {
      if (ans < dp[i]) {
        ans = dp[i];
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
