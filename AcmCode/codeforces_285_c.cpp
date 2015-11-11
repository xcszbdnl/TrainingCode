#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100007;
int n;
struct P {
  int order, d, s;
};

struct P p[maxn];

bool cmp(struct P a, struct P b) {
  return a.d > b.d;
}
int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d", &n);
  int sums = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &p[i].d, &p[i].s);
    p[i].order = i;
    sums += p[i].d;
  }
  sort(p + 1, p + 1 + n, cmp);
  int last = n;
  int pre = 1;
  int edge_num = sums / 2;
  printf("%d\n", edge_num);
  while (edge_num > 0) {
    for (int i = last; i > pre && p[pre].d > 0; i--) {
      p[i].d--;
      p[pre].d--;
      edge_num--;
      printf("%d %d\n", p[pre].order - 1, p[i].order - 1);
    }
    for (int i = last; i > pre && p[i].d == 0; i--) {
      last = i - 1;
    }
  }
  return 0;
}
