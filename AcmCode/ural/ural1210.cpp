#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
const int maxn = 1007;
const int INF = 100000007;
using namespace std;
vector<pair<int, int> > path[maxn];
queue<int> que;
int tot, dist[maxn], vis[maxn];
void spfa() {
  for (int i = 1; i <= tot; i++) {
    dist[i] = INF;
  }
  dist[1] = 0;
  que.push(1);
  vis[1] = 1;
  while (!que.empty()) {
    int cnt = que.front();
    vis[cnt] = 0;
    que.pop();
    for (int i = 0; i < path[cnt].size(); i++) {
      int v = path[cnt][i].first;
      int c = path[cnt][i].second;
      if (dist[v] > dist[cnt] + c) {
        dist[v] = dist[cnt] + c;
        if (!vis[v]) {
          vis[v] = 1;
          que.push(v);
        }
      }
    }
  }
}

int main() {
  //freopen("../in.txt", "r", stdin);
  tot = 1;
  int pre = 1;
  int k;
  scanf("%d", &k);
  for (int i = 1; i <= k; i++) {
    int line;
    scanf("%d", &line);
    for (int j = 1; j <= line; j++) {
      while (1) {
        int start, cost;
        scanf("%d", &start);
        if (!start) {
          break;
        }
        scanf("%d", &cost);
        path[tot - pre + start].push_back(make_pair(tot + j, cost));
        //printf("%d-->%d:%d\n", tot - pre + start, tot + j, cost);
      }
    }
    if (i != k) {
      char temp[10];
      scanf("%s", temp);
    }
    pre = line;
    tot += line;
  }
  spfa();
  int min_dist = INF;
  for (int i = tot - pre + 1; i <= tot; i++) {
    min_dist = min(min_dist, dist[i]);
  }
  printf("%d\n", min_dist);
  return 0;
}
