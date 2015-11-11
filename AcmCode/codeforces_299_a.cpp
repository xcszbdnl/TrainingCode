#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 2000007;

long long sums[maxn];
long long l, t, m, a, b, n;


bool check(int cnt_s) {
  long long cnt_t = (sums[cnt_s] - sums[l - 1]);
  if (sums[cnt_s] - sums[cnt_s - 1] > t) {
    return false;
  }
  if (cnt_t > m * t) {
    return false;
  }
  return true;
}
int getAns() {
  long long last = a + (l - 1) * b;
  if (last > t) {
    return -1;
  }
  int low = l;
  int high = maxn - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (check(mid)) {
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  return high;
}

int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%I64d%I64d%I64d", &a, &b, &n);
  sums[0] = 0;
  for (long long i = 1; i < maxn; i++) {
    sums[i] = sums[i - 1] + a + (i - 1) * b;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%I64d%I64d%I64d", &l, &t, &m);
    printf("%d\n", getAns());
  }
  return 0;
}
