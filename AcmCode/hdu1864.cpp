#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 3000007;
int q;
int n;
int dp[maxn];
int a[5];
int weight[maxn], num, tot_v;

void zeroPack(int cost, int value) {
  for (int i = q; i >= cost; i--) {
    dp[i] = max(dp[i], dp[i - cost] + value);
  }
}

int main() {
  //freopen("in.txt", "r", stdin);
  double tot_v;
  while (scanf("%lf%d", &tot_v, &n) != EOF) {
    if (n <= 0) {
      break;
    }
    memset(dp, 0, sizeof(dp));
    num = 0;
    q = (int)(tot_v * 100);
    for (int i = 1; i <= n; i++) {
      int m;
      memset(a, 0, sizeof(a));
      scanf("%d", &m);
      int flag = 0;
      char type;
      double money;
      for (int j = 1; j <= m; j++) {
        getchar();
        scanf("%c:%lf", &type, &money);
        int t = type - 'A' + 1;
        if (t > 3) {
          flag = 1;
        }
        else {
          a[t] += (int)(money * 100);
          if (a[t] > 600 * 100) {
            flag = 1;
          }
        }
      }
      int tot = a[1] + a[2] + a[3];
      if (tot > 1000 * 100) {
        flag = 1;
      }
      if (!flag) {
        weight[num++] = tot;
      }
    }
    for (int i = 0; i < num; i++) {
      zeroPack(weight[i], weight[i]);
    }
    double ans = dp[q] * 1.0 / 100;
    printf("%.2lf\n", ans);
  }
  return 0;
}
