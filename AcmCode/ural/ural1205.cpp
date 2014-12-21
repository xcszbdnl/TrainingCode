#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const int maxn = 207;
const double INF = 1e+300;
struct P {
  double x, y;
} p[maxn];

vector<int> ans;
int pre[maxn][maxn];
double maps[maxn][maxn];
double a, b;
int n;

double dist(int v1, int v2) {
  double x = p[v1].x - p[v2].x;
  double y = p[v1].y - p[v2].y;
  x = x * x;
  y = y * y;
  return sqrt(x + y);
}

void getPath(int i, int j) {
  if (i == j) {
    return ;
  }
  int cnt = pre[i][j];
  if (cnt <= n) {
    ans.push_back(cnt);
  }
  getPath(i, cnt);
}
void floyd() {
  for (int k = 1; k <= n + 2; k++) {
    for (int i = 1; i <= n + 2; i++) {
      for (int j = 1; j <= n + 2; j++) {
        if (maps[i][j] > maps[i][k] + maps[k][j]) {
          maps[i][j] = maps[i][k] + maps[k][j];
          pre[i][j] = pre[k][j];
        }
      }
    }
  }
}

int main() {
  //freopen("../in.txt", "r", stdin);
  scanf("%lf%lf", &a, &b);
  scanf("%d", &n);
  for (int i = 1; i <= n + 2; i++) {
    maps[i][i] = 0;
    pre[i][i] = i;
    for (int j = i + 1; j <= n + 2; j++) {
      maps[i][j] = maps[j][i] = INF;
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf("%lf%lf", &p[i].x, &p[i].y);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      maps[i][j] = maps[j][i] = dist(i, j) / a;
      pre[i][j] = i;
      pre[j][i] = j;
    }
  }
  while (1) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (!u && !v) {
      break;
    }
    maps[u][v] = maps[v][u] = dist(u, v) / b;
    pre[u][v] = u;
    pre[v][u] = v;
  }
  scanf("%lf%lf%lf%lf", &p[n + 1].x, &p[n + 1].y, &p[n + 2].x, &p[n + 2].y);
  for (int i = 1; i <= n; i++) {
    maps[i][n + 1] = maps[n + 1][i] = dist(i, n + 1) / a;
    pre[i][n + 1] = i;
    pre[n + 1][i] = n + 1;
    maps[i][n + 2] = maps[n + 2][i] = dist(i, n + 2) / a;
    pre[i][n + 2] = i;
    pre[n + 2][i] = n + 2;
  }
  maps[n + 1][n + 2] = maps[n + 2][n + 1] = dist(n + 1, n + 2) / a;
  pre[n + 1][n + 2] = n + 1;
  pre[n + 2][n + 1] = n + 2;
  floyd();
  printf("%.6f\n", maps[n + 1][n + 2]);
  getPath(n + 1, n + 2);
  printf("%d", ans.size());
  for (int i = ans.size() - 1; i >= 0; i--) {
    printf(" %d", ans[i]);
  }
  printf("\n");
  return 0;
}
