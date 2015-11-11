#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 10007;
using namespace std;

int value[maxn], n, k;

bool check(double x) {
  double up = 0;
  double down = 0;
  for (int i = 1; i <= n; i++) {
    if (value[i] > x) {
      up += value[i] - x;
    }
    else {
      down += x - value[i];
    }
  }
  double transfer = up * (1 - k * 1.0/ 100);
  if (transfer >= down) {
    return true;
  }
  return false;
}
int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &value[i]);
  }
  double low = 0;
  double high = 1000;
  while (high - low >= 1e-10) {
    double mid = (low + high) / 2;
    if (check(mid)) {
      low = mid;
    }
    else {
      high = mid;
    }
  }
  printf("%.6lf\n", high);
  return 0;
}
