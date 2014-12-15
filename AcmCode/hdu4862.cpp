#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int maxn = 100007;
const int INF = 10000007;
struct Edge {
    int u, v, cap, cost, next;
};

struct Edge edge[maxn];
int head[maxn], dist[maxn], vis[maxn], pre[maxn];
int n, m, k, edge_num, source, dest, k_num, cost, flow;
int step[4][2] = {{1, 0}, {0, 1}};
char maps[107][107];
queue<int> que;
int spfa() {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= dest; i++) {
        dist[i] = INF;
    }
    que.push(source);
    dist[source] = 0;
    vis[source] = 0;
    while (!que.empty()) {
        int cnt = que.front();
        que.pop();
        vis[cnt] = 0;
        for (int i = head[cnt]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].cap > 0 && dist[v] > dist[cnt] + edge[i].cost) {
                dist[v] = dist[cnt] + edge[i].cost;
                pre[v] = i;
                if (!vis[v]) {
                    vis[v] = 1;
                    que.push(v);
                }
            }
        }
    }
    if (dist[dest] == INF) {
        return 0;
    }
    int min_flow = INF;
    int pre_num;
    for (int i = dest; i != source; i = edge[pre_num].u) {
        pre_num = pre[i];
        if (min_flow > edge[pre_num].cap) {
            min_flow = edge[pre_num].cap;
        }
    }
    for (int i = dest; i != source; i = edge[pre_num].u) {
        pre_num = pre[i];
        edge[pre_num].cap -= min_flow;
        edge[pre_num ^ 1].cap += min_flow;
        cost += min_flow * edge[pre_num].cost;
    }
    flow += min_flow;
    return 1;
}
void addEdge(int u, int v, int cap_1, int cap_2, int cost_1, int cost_2) {
    edge[edge_num].u = u;
    edge[edge_num].v = v;
    edge[edge_num].cap = cap_1;
    edge[edge_num].cost = cost_1;
    edge[edge_num].next = head[u];
    head[u] = edge_num;
    edge_num++;

    edge[edge_num].u = v;
    edge[edge_num].v = u;
    edge[edge_num].cap = cap_2;
    edge[edge_num].cost = cost_2;
    edge[edge_num].next = head[v];
    head[v] = edge_num;
    edge_num++;
}
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    int ncase = 1;
    while (test_case--) {
        printf("Case %d : ", ncase++);
        memset(head, -1, sizeof(head));
        edge_num = 0;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; i++) {
            scanf("%s", maps[i]);
        }
        source = 0;
        dest = 2 * n * m + 2;
        k_num = 2 * n * m + 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                addEdge(source, i * m + j + 1, 1, 0, 0, 0);
                addEdge(n * m + i * m + j + 1, dest, 1, 0, 0, 0);
                addEdge(k_num, n * m + i * m + j + 1, 1, 0, 0, 0);
            }
        }
        addEdge(source, k_num, k, 0, 0, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int s = 1; s < m; s++) {
                    int next_y = s + j;
                    if (next_y < m) {
                        int e = 0;
                        if (maps[i][j] == maps[i][next_y]) {
                            e = maps[i][j] - '0';
                        }
                        addEdge(i * m + j + 1, 1 + n * m + i * m + next_y, 1, 0, next_y - j - 1 - e, -(next_y - j - 1 - e));
//                        printf("%d---%d\n", i * m + j, n * m + next_x * m + j);
                    }
                }
                for (int s = 1; s < n; s++) {
                    int next_x = i + s;
                    if (next_x < n) {
                        int e = 0;
                        if (maps[i][j] == maps[next_x][j]) {
                            e = maps[i][j] - '0';
                        }
                        addEdge(1 + i * m + j, 1 + n * m + next_x * m + j, 1, 0, next_x - i - 1 - e, -(next_x - i - 1 - e));
//                        printf("%d----%d\n", i * m + j, n * m + next_x * m + j);
                    }
                }
            }
        }
        cost = flow = 0;
        while (spfa()) {
            ;
        }
        if (flow != n * m) {
            printf("-1\n");
        }
        else {
            cost = -cost;
            printf("%d\n", cost);
        }
    }
    return 0;
}
