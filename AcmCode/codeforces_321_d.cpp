#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 20;
long long maps[maxn][maxn];
long long dp[1 << (18)][maxn];
long long ans, value[maxn];
int n, m, k;
int main() {
  //freopen("in.txt", "r", stdin);
  memset(maps, 0, sizeof(maps));
  memset(dp, 0, sizeof(dp));
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; i++) {
    cin >> value[i];
  }
  for (int i = 1; i <= k; i++) {
    long long a, b, c;
    cin >> a >> b >> c;
    maps[a - 1][b - 1] = c;
  }
  for (int i = 0; i < n; i++) {
    dp[1 << i][i] = value[i];
  }
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        for (int k = 0; k < n; k++) {
          if (!(i & (1 << k))) {
            long long temp = dp[i][j] + value[k] + maps[j][k];
            dp[i | (1 << k)][k] = max(dp[i | (1 << k)][k], temp);
          }
        }
      }
    }
  }
  for (int i = 0; i < (1 << n); i++) {
    int num = 0;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        num++;
      }
    }
    if (num == m) {
      for (int j = 0; j < n; j++) {
        ans = max(ans, dp[i][j]);
      }
    }
  }
  cout << ans << endl;
  return 0;
}
