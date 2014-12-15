#include <cstdio>
#include <cstring>

const int maxn = 100007;
const int INF = 100000007;
struct Edge {
    int start, dest, cap, cost, next;
};

struct Edge edge[maxn];
int head[maxn], dist[maxn], vis[maxn], que[maxn], pre[maxn], flow, costs;
int source, destination, n, edge_number;

int trash[170][170];
void addEdge(int start, int dest, int cap_1, int cap_2, int cost_1, int cost_2) {
    edge[edge_number].start = start;
    edge[edge_number].dest = dest;
    edge[edge_number].cap = cap_1;
    edge[edge_number].cost = cost_1;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;

    edge[edge_number].start = dest;
    edge[edge_number].dest = start;
    edge[edge_number].cap = cap_2;
    edge[edge_number].cost = cost_2;
    edge[edge_number].next = head[dest];
    head[dest] = edge_number;
    edge_number++;
}


int spfa() {
    for (int i = 0; i <= 2 * n + 1; i++) {
        dist[i] = INF;
    }
    memset(vis, 0, sizeof(vis));
    dist[source] = 0;
    int front = 0;
    int rear = 1;
    vis[source] = 1;
    que[front] = source;
    while (front < rear) {
        int cnt = que[front];
        for (int i = head[cnt]; i != -1; i = edge[i].next) {
            int next = edge[i].dest;
            if (edge[i].cap > 0 && dist[next] > dist[cnt] + edge[i].cost) {
                dist[next] = dist[cnt] + edge[i].cost;
                pre[next] = i;
                if (!vis[next]) {
                    vis[next] = 1;
                    que[rear++] = next;
                }
            }
        }
        front++;
        vis[cnt] = 0;
    }
    if (dist[destination] == INF) {
        return 0;
    }
    int min_flow = INF;
    int pre_number;
    for (int i = destination; i != source; i = edge[pre_number].start) {
        pre_number = pre[i];
        if (min_flow > edge[pre_number].cap) {
            min_flow = edge[pre_number].cap;
        }
    }
    for (int i = destination; i != source; i = edge[pre_number].start) {
        pre_number = pre[i];
        edge[pre_number].cap -= min_flow;
        edge[pre_number ^ 1].cap += min_flow;
//        printf("cost:%d\n", edge[pre_number].cost);
        costs += edge[pre_number].cost * min_flow;
    }
//    printf("min_flow: %d\n", min_flow);
    flow += min_flow;
    return 1;
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    edge_number = 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &trash[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        int sums = 0;
        for (int j = 1; j <= n; j++) {
            sums += trash[j][i];
        }
        for (int j = 1; j <= n; j++) {
            int temp = sums;
            temp -= trash[j][i];
            addEdge(i, j + n, 1, 0, temp, -temp);
//            printf("%d %d %d\n",i, j + n, temp);
        }
    }
    source = 0;
    destination = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        addEdge(source, i, 1, 0, 0, 0);
        addEdge(i + n, destination, 1, 0, 0, 0);
    }
    flow = costs = 0;
    while (spfa()) {
        //printf("loop.........\n");
        ;
    }
    printf("%d\n", costs);
    return 0;
}
