#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 107;
const int maxv = 10007;
struct Product {
    int b,c;
};

struct Product product[20][maxn];
int dp[12][10007];
int num[20];

int n, money, k;

int getMax(int a, int b, int c) {
    int t = a > b ? a : b;
    return t > c ? t : c;
}
int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d%d%d", &n, &money, &k) != EOF) {
    memset(num, 0, sizeof(num));
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; i++) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      num[a]++;
      product[a][num[a]].b = b;
      product[a][num[a]].c = c;
    }
    for (int i = 0; i <= money; i++) {
      dp[0][i] = 0;
    }
    for (int i = 1; i <= k; i++) {
      for (int m = 1; m <= num[i]; m++) {
        for (int j = money; j >= product[i][m].b; j--) {
          dp[i][j] = getMax(dp[i][j], dp[i - 1][j - product[i][m].b] + product[i][m].c, dp[i][j - product[i][m].b] + product[i][m].c);
        }
      }
    }
    if (dp[k][money] < 0) {
      printf("Impossible\n");
    }
    else {
      printf("%d\n", dp[k][money]);
    }
  }
  return 0;
}
