#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100007;

int num[maxn];
int vis[maxn];
int dp[maxn];
int n, d;
int max_len;
void search(int cnt, int step) {
  if (dp[cnt] != -1) {
    return ;
  }
  if (cnt > max_len) {
    dp[cnt] = 0;
    return ;
  }
  if (step == 0) {
    return ;
  }
  search(cnt + step - 1, step - 1);
  search(cnt + step, step);
  search(cnt + step + 1, step + 1);
  dp[cnt] = max(dp[cnt], dp[cnt + step - 1] + num[cnt]);
  dp[cnt] = max(dp[cnt], dp[cnt + step] + num[cnt]);
  dp[cnt] = max(dp[cnt], dp[cnt + step + 1] + num[cnt]);
  
}
int main() {
  //freopen("in.txt", "r", stdin);
  memset(dp, -1, sizeof(dp));
  memset(num, 0, sizeof(num));
  scanf("%d%d", &n, &d);
  max_len = 0;
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    num[x]++;
    max_len = max(max_len, x);
  }
  search(d, d);
  int ans = 0, loc;
  for (int i = 1; i < maxn; i++) {
    ans = max(ans, dp[i]);
  }
  printf("%d\n", ans);
  return 0;
}
