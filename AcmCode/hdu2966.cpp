#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 100007;
using namespace std;

struct P {
  int x[3];
  int id;
};

struct P p[maxn * 4];
int n, dimention, cmp_dimention;
long long ans[maxn * 4], max_dist;


bool cmp(struct P a, struct P b) {
  return a.x[cmp_dimention] < b.x[cmp_dimention];
}
void buildTree(int left, int right, int depth) {
  if (left >= right) {
    return ;
  }
  int mid = (left + right) >> 1;
  cmp_dimention = (depth % dimention) + 1;
  nth_element(p + left, p + mid, p + right + 1, cmp);
  buildTree(left, mid - 1, depth + 1);
  buildTree(mid + 1, right, depth + 1);
}

long long dist(struct P &a, struct P &b) {
  long long x = a.x[1] - b.x[1];
  long long y = a.x[2] - b.x[2];
  x *= x;
  y *= y;
  x += y;
  return x == 0 ? -1 : x;
}
void find(struct P &cnt_p, int left, int right, int depth) {
  if (left > right) {
    return ;
  }
  int cnt = (depth % dimention) + 1;
  int mid = (left + right) >> 1;
  long long cnt_dist = dist(cnt_p, p[mid]);
  if (cnt_dist != -1 && (max_dist == -1 || cnt_dist < max_dist)) {
    max_dist = cnt_dist;
  }
  if (left == right) {
    return ;
  }
  if (cnt_p.x[cnt] < p[mid].x[cnt]) {
    find(cnt_p, left, mid - 1, depth + 1);
    long long d = p[mid].x[cnt] - cnt_p.x[cnt];
    d = d * d;
    if (d < max_dist) {
      find(cnt_p, mid + 1, right, depth + 1);
    }
  }
  else {
    find(cnt_p, mid + 1, right, depth + 1);
    long long d = p[mid].x[cnt] - cnt_p.x[cnt];
    d = d * d;
    if (d < max_dist) {
      find(cnt_p, left, mid - 1, depth + 1);
    }
  }
}

int main() {
  freopen("in.txt", "r", stdin);
  int test_case;
  scanf("%d", &test_case);
  while (test_case--) {
    scanf("%d", &n);
    dimention = 2;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &(p[i].x[1]), &(p[i].x[2]));
      p[i].id = i;
    }
    buildTree(1, n, 0);
    for (int i = 1; i <= n; i++) {
      max_dist = -1;
      find(p[i], 1, n, 0);
      ans[p[i].id] = max_dist;
    }
    for (int i = 1; i <= n; i++) {
      printf("%lld\n", ans[i]);
    }
  }
  return 0;
}
