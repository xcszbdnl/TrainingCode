#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <map>
using namespace std;
const int maxn = 20007;
int pre[maxn], sccno[maxn], lowlink[maxn], in[maxn], vis[maxn], head[maxn];
stack<int> S;
int n, dfs_clock, scc_cnt, edge_num;
int maps[2005][2006];

struct Edge {
  int u, v, next;
} edge[100007];
void dfs(int u) {
  pre[u] = lowlink[u] = ++dfs_clock;
  S.push(u);
  for (int i = head[u]; i != -1; i = edge[i].next) {
    int v = edge[i].v;
    if (!pre[v]) {
      dfs(v);
      lowlink[u] = min(lowlink[u], lowlink[v]);
    }
    else if (!sccno[v]) {
      lowlink[u] = min(lowlink[u], pre[v]);
    }
  }
  if (lowlink[u] == pre[u]) {
    scc_cnt++;
    for (; ;) {
      int x = S.top();
      S.pop();
      sccno[x] = scc_cnt;
      if (x == u) {
        break;
      }
    }
  }
}

void findScc() {
  dfs_clock = scc_cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!pre[i]) {
      dfs(i);
    }
  }
}

void addEdge(int u, int v) {
  edge[edge_num].u = u;
  edge[edge_num].v = v;
  edge[edge_num].next = head[u];
  head[u] = edge_num;
  edge_num++;
}
int main() {
  //freopen("../in.txt", "r", stdin);
  memset(head, -1, sizeof(head));
  edge_num = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int a;
    scanf("%d", &a);
    while (a) {
      addEdge(i, a);
      scanf("%d", &a);
    }
  }
  findScc();
  for (int i = 1; i <= n; i++) {
    for (int j = head[i]; j != -1; j = edge[j].next) {
      int v = edge[j].v;
      int v1 = sccno[i];
      int v2 = sccno[v];
      if (v1 != v2 && !maps[v1][v2]) {
        maps[v1][v2] = 1;
        in[v2]++;
      }
    }
  }
  int num = 0, node;
  for (int i = 1; i <= scc_cnt; i++) {
    if (!in[i] && num <= 2) {
      num++;
      node = i;
    }
  }
  if (num >= 2 || num == 0) {
    printf("0\n");
  }
  else {
    for (int i = 1; i <= n; i++) {
      if (sccno[i] == node) {
        printf("%d ", i);
      }
    }
    printf("0\n");
  }
  return 0;
}
