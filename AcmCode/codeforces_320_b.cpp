#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>


using namespace std;

const int maxn = 200007;

long long pre[maxn], suf[maxn];
long long a[maxn];
int n, k, x;
long long cnt;

int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d%d%d", &n, &k, &x);
  memset(pre, 0, sizeof(pre));
  memset(suf, 0, sizeof(suf));
  cnt = 1;
  while(k--) {
    cnt *= x;
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1] | a[i];
  }
  for (int i = n; i >= 1; i--) {
    suf[i] = suf[i + 1] | a[i];
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    long long temp = pre[i - 1] | (a[i] * cnt) | (suf[i + 1]);
    ans = max(ans, temp);
  }
  cout << ans << endl;
}
