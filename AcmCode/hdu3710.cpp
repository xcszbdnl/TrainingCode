#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 20007;
const int INF = 10000007;
struct Edge {
    int u, v, cost, status, next;
};

struct Edge edge[maxn * 10];

int head[maxn], vis[maxn], dist[maxn];
int n, m, edge_num, flag, ans;

void addEdge(int u, int v, int cost, int status) {
    edge[edge_num].u = u;
    edge[edge_num].v = v;
    edge[edge_num].cost = cost;
    edge[edge_num].status = status;
    edge[edge_num].next = head[u];
    head[u] = edge_num;
    edge_num++;

    edge[edge_num].u = v;
    edge[edge_num].v = u;
    edge[edge_num].cost = cost;
    edge[edge_num].status = status;
    edge[edge_num].next = head[v];
    head[v] = edge_num;
    edge_num++;
}

void prim(int cnt) {
    for (int i = 1; i <= n; i++) {
        vis[i] = 0;
        dist[i] = INF;
    }
    cnt == 1 ? dist[2] = 0: dist[1] = 0;
    for (int i = 1; i < n; i++) {
        int min_num = INF;
        int point;
        for (int i = 1; i <= n; i++) {
            if (i != cnt && !vis[i] && dist[i] < min_num) {
                min_num = dist[i];
                point = i;
            }
        }
        if (min_num == INF) {
            flag = 1;
            return ;
        }
        vis[point] = 1;
        ans += min_num;
        for (int i = head[point]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (!vis[v] && v != cnt) {
                if (edge[i].status) {
                    dist[v] = 0;
                }
                else {
                    if (dist[v] > edge[i].cost) {
                        dist[v] = edge[i].cost;
                    }
                }
            }
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(head, - 1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        edge_num = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            addEdge(a, b, c, d);
        }
        for (int i = 1; i <= n; i++) {
            ans = 0;
            flag = 0;
            prim(i);
            if (!flag) {
                printf("%d\n", ans);
            }
            else {
                printf("inf\n");
            }
        }
    }
    return 0;
}
