#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100007;
const int INF = 10000007;
int dp[maxn];
int a, b, v, n;

void completePack(int cost, int value) {
  for (int i = cost; i <= v; i++) {
    dp[i] = min(dp[i], dp[i - cost] + value);
  }
}

int main() {
  //freopen("in.txt", "r", stdin);
  int test_case;
  scanf("%d", &test_case);
  while (test_case--) {
    scanf("%d%d", &a, &b);
    v = b - a;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= v; i++) {
      dp[i] = INF;
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      completePack(y, x);
    }
    if (dp[v] == INF) {
      printf("This is impossible.\n");
    }
    else {
      printf("The minimum amount of money in the piggy-bank is %d.\n", dp[v]);
    }
  }
  return 0;
}
