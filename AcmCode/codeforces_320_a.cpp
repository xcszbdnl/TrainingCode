#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int a, b;
double ans;
int flag;
const double INF = 1e50;
int checkNegative(long long cnt_k) {
  double x = (a + b) * 1.0 / (2 * cnt_k + 2);
  if (x >= b && a >= (2 * cnt_k + 1) * x && a <= (2 * cnt_k + 2) * x) {
    return true;
  }
  else {
    return false;
  }
}

int checkPositive(long long cnt_k) {
  double x = (a - b) * 1.0 / (2 * cnt_k);
  if (x >= b && a >= 2 * cnt_k * x && a <= (2 * cnt_k + 1) * x) {
    return true;
  }
  else {
    return false;
  }
}
int main() {

  scanf("%d%d", &a, &b);
  long long high = a + b;
  long long low = 0;
  ans = INF;
  while (low <= high) {
    long long mid = (low + high) >> 1;
    if (checkPositive(mid)) {
      flag = 1;
      double temp = (a - b) * 1.0 / (2 * mid);
      ans = min(ans, temp);
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  low = 0;
  high = a + b;
  while (low <= high) {
    long long mid = (low + high) >> 1;
    if (checkNegative(mid)) {
      flag = 1;
      double temp = (a + b) * 1.0 / (2 * mid + 2);
      ans = min(ans, temp);
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  if (flag) {
    printf("%.9lf\n", ans);
  }
  else {
    printf("-1\n");
  }
  return 0;
}
