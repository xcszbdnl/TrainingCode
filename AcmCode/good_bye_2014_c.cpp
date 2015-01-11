#include <cstdio>
#include <cstring>

const int maxn = 2000;


int tree[maxn + 7], w[maxn + 7], b[maxn + 7], cnt[maxn + 7];
int n, m;

int lowbit(int x) {
  return x & (-x);
}
void add(int x, int d) {
  while (x < maxn) {
    tree[x] += d;
    x += lowbit(x);
  }
}

int sums(int x) {
  int ret = 0;
  while (x > 0) {
    ret += tree[x];
    x -= lowbit(x);
  }
  return ret;
}

int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &w[i]);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", &b[i]);
  }
  memset(cnt, 0, sizeof(cnt));
  int ans = 0;
  int top = n + 1;
  for (int i = 1; i <= m; i++) {
    int flag = 0;
    int loc;
    for (int j = 1; j < maxn; j++) {
      if (cnt[j] == b[i]) {
        flag = 1;
        loc = j;
        break;
      }
    }
    if (flag) {
      ans += sums(top) - sums(loc);
      add(loc, -w[cnt[loc]]);
      add(top, w[cnt[loc]]);
      cnt[top] = cnt[loc];
      cnt[loc] = 0;
      top++;
    }
    else {
      ans += sums(top);
      add(top, w[b[i]]);
      cnt[top] = b[i];
      top++;
    }
  }
  printf("%d\n", ans);
  return 0;
}
