#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 500007;
const long long INF = 100000000000007ll;
struct Edge {
    int train;
    int start, dest, next;
    long long val;
};

struct Train {
    int dest, e[2];
    long long val;
};
struct Edge edge[maxn * 2];
struct Train train[maxn];
int vis[maxn], que[maxn], head[maxn], pre[maxn];
long long dist[maxn];
int n, m, k, edge_number;

void addEdge(int start, int dest, long long val, int train) {
    edge[edge_number].start = start;
    edge[edge_number].dest = dest;
    edge[edge_number].val = val;
    edge[edge_number].train = train;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;

    edge[edge_number].dest = start;
    edge[edge_number].start = dest;
    edge[edge_number].val = val;
    edge[edge_number].train = train;
    edge[edge_number].next = head[dest];
    head[dest] = edge_number;
    edge_number++;
}
void spfa() {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= n; i++) {
        dist[i] = INF;
    }
    for (int i = 1; i <= k; i++) {
        int dest = train[i].dest;
        if (train[i].val < dist[dest]) {
            dist[dest] = train[i].val;
            pre[dest] = train[i].e[0];
        }
    }
    dist[1] = 0;
    vis[1] = 1;
    que[0] = 1;
    int front = 0;
    int rear = 1;
    while (front < rear) {
        int cnt = que[front];
        for (int i = head[cnt]; i != -1; i = edge[i].next) {
            int next = edge[i].dest;
            if (dist[next] >= dist[cnt] + edge[i].val) {
                if (!edge[i].train) {
                    pre[next] = i;
                }
                dist[next] = dist[cnt] + edge[i].val;
                if (!vis[next]) {
                    vis[next] = 1;
                    que[rear] = next;
                    rear++;
                    rear %= maxn;
                }
            }
        }
        front++;
        front %= maxn;
        vis[cnt] = 0;
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &m, &k);
    memset(head, -1, sizeof(head));
    edge_number = 0;
    for (int i = 1; i <= m; i++) {
        long long a, b, c;
        scanf("%I64d%I64d%I64d", &a, &b, &c);
        addEdge(a, b, c, 0);
    }
    for (int i = 1; i <= k; i++) {
        long long b, c;
        scanf("%I64d%I64d", &b, &c);
        addEdge(1, b, c, 1);
        train[i].e[0] = edge_number - 2;
        train[i].e[1] = edge_number - 1;
        train[i].dest = b;
        train[i].val = c;
    }
    spfa();
    int ans = 0;
//    for (int i = 1; i <= n; i++) {
//        printf("dist[%d]:%d------info:%d\n", i, dist[i], info[i]);
//    }
    for (int i = 1; i <= k; i++) {
        int dest = train[i].dest;
        if (dist[dest] < train[i].val) {
            ans++;
        }
        else if (dist[dest] == train[i].val && !(train[i].e[0] == pre[dest] || train[i].e[1] == pre[dest])) {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
