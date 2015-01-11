#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100007;
int n, q;

struct Edge {
  int u, v, cost, end, next;
};

struct Seg {
  int left, right;
  double val, num, sums;
};
struct Seg seg[maxn * 4];
struct Edge edge[maxn * 2];
int head[maxn], son_num[maxn], vis[maxn], edge_num;
void pushUp(int order) {
  seg[order].sums = seg[order * 2].sums + seg[order * 2 + 1].sums;
}

void build(int order, int left, int right) {
  seg[order].left = left;
  seg[order].right = right;
  seg[order].sums = 0;
  int mid = (left + right) >> 1;
  if (left == right) {
    left--;
    left *= 2;
    if (edge[left].end == 0) {
      left ^= 1;
    }
    seg[order].val = edge[left].cost;
    seg[order].num = son_num[edge[left].end];
    seg[order].sums = seg[order].val * seg[order].num * (n - seg[order].num) * (n - seg[order].num - 1) + seg[order].val * seg[order].num * (seg[order].num - 1) * (n - seg[order].num);    
    return ;
  }
  build(order * 2, left, mid);
  build(order * 2 + 1, mid + 1, right);
  pushUp(order);
}
void update(int order, int left, int right, int val) {
  int mid = (seg[order].left + seg[order].right) >> 1;
  if (left == seg[order].left && right == seg[order].right) {
    seg[order].val = val;
    seg[order].sums = seg[order].val * seg[order].num * (n - seg[order].num) * (n - seg[order].num - 1) + seg[order].val * seg[order].num * (seg[order].num - 1) * (n - seg[order].num);
    return ;
  }
  if (right <= mid) {
    update(order * 2, left, right, val);
  }
  else if (left > mid) {
    update(order * 2 + 1, left, right, val);
  }
  pushUp(order);
}


void dfs(int cnt) {
  son_num[cnt] = 1;
  for (int i = head[cnt]; i != -1; i = edge[i].next) {
    int v = edge[i].v;
    if (!vis[v]) {
      edge[i].end = v;
      vis[v] = 1;
      dfs(v);
      son_num[cnt] += son_num[v];
    }
  }
}

void addEdge(int a, int b, int c) {
  edge[edge_num].u = a;
  edge[edge_num].v = b;
  edge[edge_num].cost = c;
  edge[edge_num].next = head[a];
  edge[edge_num].end = 0;
  head[a] = edge_num;
  edge_num++;

  edge[edge_num].u = b;
  edge[edge_num].v = a;
  edge[edge_num].cost = c;
  edge[edge_num].next = head[b];
  head[b] = edge_num;
  edge[edge_num].end = 0;
  edge_num++;
}

int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d", &n);
  memset(head, -1, sizeof(head));
  memset(son_num, 0, sizeof(son_num));
  memset(vis, 0, sizeof(vis));
  edge_num = 0;
  for (int i = 1; i < n; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    addEdge(a, b, c);
  }
  vis[1] = 1;
  dfs(1);
  int q;
  scanf("%d", &q);
  build(1, 1, n - 1);
  for (int i = 1; i <= q; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    update(1, a, a, b);
    double ans = seg[1].sums;
    double tot = n;
    tot = tot * (tot - 1) * (tot - 2) / 6;
    ans = ans / tot;
    printf("%.6f\n", ans);    
  }
  return 0;
}
