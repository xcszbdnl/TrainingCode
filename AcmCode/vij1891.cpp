#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>


using namespace std;
const int maxn = 2000;
const int INF = 1000007;
typedef long long ULL;
struct Edge {
    int u, v, cost, cap;
    ULL next;
};

struct Edge edge[maxn * 100];
int head[maxn], n, k;
ULL val[maxn], sums, flow, dist[maxn];
int que[maxn * 100], vis[maxn], pre[maxn];
int source, dest, edge_num;

bool spfa() {
    for (int i = 0; i <= dest; i++) {
        dist[i] = (1ll << 62);
    }
    memset(vis, 0, sizeof(vis));
    dist[source] = 0;
    int front = 0;
    int rear = 1;
    vis[source] = 1;
    que[front] = source;
    while (front < rear) {
        int cnt = que[front];
        vis[cnt] = 0;
        for (int i = head[cnt]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].cap > 0 && (dist[v] > dist[cnt] + edge[i].cost)) {
                dist[v] = dist[cnt] + edge[i].cost;
                pre[v] = i;
                if (!vis[v]) {
                    vis[v] = 1;
                    que[rear++] = v;
                }
            }
        }
        front++;
    }
    if (dist[dest] == (1ll << 62)) {
        return 0;
    }
    int min_flow = INF;
    int pre_edge;
    for (int i = dest; i != source; i = edge[pre_edge].u) {
        pre_edge = pre[i];
        if (min_flow > edge[pre_edge].cap) {
            min_flow = edge[pre_edge].cap;
        }
    }
    for (int i = dest; i != source; i = edge[pre_edge].u) {
        pre_edge = pre[i];
        sums += min_flow * edge[pre_edge].cost;
        edge[pre_edge].cap -= min_flow;
        edge[pre_edge ^ 1].cap += min_flow;
    }
    flow += min_flow;
    return 1;
}

void addEdge(int u, int v, int cap_1, int cap_2, ULL cost_1, ULL cost_2) {
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
    edge_num++;
}

int main() {
    freopen("in.txt", "r", stdin);
    memset(head, -1, sizeof(head));
    edge_num = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= 3 * n; i++) {
        cin >> val[i];
    }
    edge_num = 0;
    source = 0;
    dest = 2 * n + 3;
    for (int i = 1; i <= n; i++) {
        addEdge(i, n + i, 1, 0, -val[i + n], val[i + n]);
//        printf("%d-->%d\n", i, n + i);
    }
    for (int i = 1; i <= 2 * n - 1; i++) {
        addEdge(i, i + 1, k, 0, 0, 0);
//        printf("%d-->%d\n", i, 1 + i);
    }
    addEdge(source, 2 * n + 1, k, 0, 0, 0);
//    printf("%d-->%d\n", source, 2 * n + 1);
    addEdge(2 * n + 1, 1, k, 0, 0, 0);
//    printf("%d-->%d\n", 2 * n + 1, 1);
    for (int i = 1; i <= n; i++) {
        addEdge(2 * n + 1, i, 1, 0, -val[i], val[i]);
//        printf("%d-->%d\n", 2 * n + 1, i);
    }
    addEdge(2 * n + 2, dest, k, 0, 0, 0);
//    printf("%d-->%d\n", 2 * n + 2, dest);
    addEdge(2 * n, 2 * n + 2, k, 0, 0, 0);
//    printf("%d-->%d\n", 2 * n, 2 * n + 2);
    for (int i = n + 1; i <= 2 * n; i++) {
        addEdge(i, 2 * n + 2, 1, 0, -val[n + i], val[n + i]);
//        printf("%d-->%d\n", i, 2 * n + 2);
    }
    sums = flow = 0;
    while (spfa()) {
        ;
    }
    cout << -sums << endl;
}
