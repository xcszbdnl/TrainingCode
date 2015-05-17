#include <cstdio>
#include <cstring>


const int maxn = 3007;
const int INF = 10007;
struct Edge {
  int start, end, next;
};

struct Edge edge[maxn * 2];
int n, m, s1, t1, l1, s2, t2, l2, edge_number, head[maxn];
int dist[maxn], que[maxn * 2], num, dp[maxn][maxn];


void bfs(int s) {
  memset(dist, -1, sizeof(dist));
  dist[s] = 0;
  int front = 0, rear = 1;
  for (int i = 1; i <= n; i++) {
    dp[s][i] = INF;
  }
  dp[s][s] = 0;
  que[0] = s;
  while (front < rear) {
    int cnt = que[front];
    for (int i = head[cnt]; i != -1; i = edge[i].next) {
      int end = edge[i].end;
      if (dist[end] == -1) {
        dp[s][end] = dist[cnt] + 1;
        dist[end] = dist[cnt] + 1;
        que[rear++] = end;
      }
    }
    front++;
  }
}


void addEdge(int start, int end) {
  edge[edge_number].start = start;
  edge[edge_number].end = end;
  edge[edge_number].next = head[start];
  head[start] = edge_number;
  edge_number++;

  edge[edge_number].start = end;
  edge[edge_number].end = start;
  edge[edge_number].next = head[end];
  head[end] = edge_number;
  edge_number++;
}
int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d%d", &n, &m);
  edge_number = 0;
  memset(head, -1, sizeof(head));
  for (int i = 1; i <= m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    addEdge(a, b);
  }
  scanf("%d%d%d%d%d%d", &s1, &t1, &l1, &s2, &t2, &l2);
  for (int i = 1; i <= n; i++) {
    bfs(i);
  }
  if (dp[s1][t1] >  l1 || dp[s2][t2] > l2) {
    printf("-1\n");
    return 0;
  }
  else {
    int temp_ans = m - dp[s1][t1] - dp[s2][t2];
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (dp[s1][i] + dp[i][j] + dp[j][t1] <= l1 && dp[s2][i] + dp[i][j] + dp[j][t2] <= l2) {
          int cnt_ans = m - dp[s1][i] - dp[s2][i] - dp[i][j] - dp[j][t1] - dp[j][t2];
          if (cnt_ans > temp_ans) {
            temp_ans = cnt_ans;
          }
        }
        if (dp[t1][i] + dp[i][j] + dp[j][s1] <= l1 && dp[s2][i] + dp[i][j] + dp[j][t2] <= l2) {
          int cnt_ans = m - dp[t1][i] - dp[s2][i] - dp[i][j] - dp[j][s1] - dp[j][t2];
          if (cnt_ans > temp_ans) {
            temp_ans = cnt_ans;
          }
        }
      }
    }
    printf("%d\n", temp_ans);
  }
  return 0;
}
