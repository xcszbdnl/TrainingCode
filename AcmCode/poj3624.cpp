#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 20006;

int dp[maxn];
int m, n, v;
void zeroPack(int cost, int value) {
  for (int i = v; i >= cost; i--) {
    dp[i] = max(dp[i], dp[i - cost] + value);
  }
}

int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d%d", &n, &m) != EOF) {
    v = m;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      zeroPack(a, b);
    }
    printf("%d\n", dp[v]);
  }
  return 0;
}
