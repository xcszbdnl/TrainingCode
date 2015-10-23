#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 200007;
struct Edge {
  int u, v;
  int next;
};

struct Edge edge[maxn];
int n, m, edge_num, ans;
int head[maxn], vis[maxn], value[maxn], cats[maxn], fa[maxn];

void addEdge(int u, int v) {
  edge[edge_num].u = u;
  edge[edge_num].v = v;
  edge[edge_num].next = head[u];
  head[u] = edge_num;
  edge_num++;

  edge[edge_num].u = v;
  edge[edge_num].v = u;
  edge[edge_num].next = head[v];
  head[v] = edge_num;
  edge_num++;
}

void dfs(int cnt) {
  if (value[cnt]) {
    cats[cnt] = cats[fa[cnt]] + value[cnt];
  }
  else {
    cats[cnt] = 0;
  }
  if (cats[cnt] > m) {
    return ;
  }
  int son_num = 0;
  for (int i = head[cnt]; i != -1; i = edge[i].next) {
    int v = edge[i].v;
    if (!vis[v]) {
      fa[v] = cnt;
      vis[cnt] = 1;
      son_num++;
      dfs(v);
    }
  }
  if (son_num == 0) {
    ans++;
  }
}
int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d%d", &n, &m);
  memset(head, -1, sizeof(head));
  memset(vis, 0, sizeof(vis));
  ans = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &value[i]);
  }
  for (int i = 1; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    addEdge(a, b);
  }
  vis[1] = 1;
  dfs(1);
  printf("%d\n", ans);
  return 0;
}
