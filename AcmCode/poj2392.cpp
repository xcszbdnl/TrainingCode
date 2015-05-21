#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 40007;

struct Obj {
  int a, h, c;
};
int k;
struct Obj obj[maxn];

int dp[maxn];

bool cmp(struct Obj a, struct Obj b) {
  return a.a < b.a;
}
void zeroPack(int cost, int value, int tot) {
  for (int i = tot; i >= cost; i--) {
    dp[i] = max(dp[i], dp[i - cost] + value);
  }
}

void completePack(int cost, int value, int tot) {
  for (int i = cost; i <= tot; i++) {
    dp[i] = max(dp[i], dp[i - cost] + value);
  }
}
void multiPack(int cost, int value, int times, int tot) {
  if (cost * times >= tot) {
    completePack(cost, value, tot);
  }
  else {
    int k = 1;
    while (k < times) {
      zeroPack(k * cost, k * value, tot);
      times -= k;
      k *= 2;
    }
    zeroPack(times * cost, times * value, tot);
  }
}
int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d", &k) != EOF) {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= k; i++) {
      scanf("%d%d%d", &obj[i].h, &obj[i].a, &obj[i].c);
    }
    sort(obj + 1, obj + 1 + k, cmp);
    for (int i = 1; i <= k; i++) {
      multiPack(obj[i].h, obj[i].h, obj[i].c, obj[i].a);
    }
    int ans = 0;
    for (int i = 0; i <= obj[k].a; i++) {
      ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
