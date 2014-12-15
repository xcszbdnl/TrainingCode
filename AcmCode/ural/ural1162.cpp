#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
const int maxn = 10007;
const double eps = 1e-8;
struct Edge {
    int u, v, next;
    double r, c;
};


int sgn(double x) {
    return x < -eps ? -1 : x > eps;
}
struct Edge edge[maxn];
double dist[maxn];
int n, m, source, vis[maxn], head[maxn], edge_num;
double original;
queue<int> que;
int spfa() {
    for (int i = 1; i <= n; i++) {
        dist[i] = 0;
    }
    dist[source] = original;
    vis[source] = 1;
    memset(vis, 0, sizeof(vis));
    que.push(source);
    while (!que.empty()) {
        int cnt = que.front();
        que.pop();
        vis[cnt] = 0;
        for (int i = head[cnt]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (sgn(dist[cnt] - edge[i].c) <= 0) {
                continue;
            }
            double p = (dist[cnt] - edge[i].c) * edge[i].r;
            if (sgn(p - dist[v]) > 0) {
                dist[v] = p;
                if (!vis[v]) {
                    vis[v] = 1;
                    que.push(v);
                }
            }
        }
    }
    if (sgn(dist[source] - original) > 0) {
        return 1;
    }
    return 0;
}


void addEdge(int u, int v, double rate, double cost) {
    edge[edge_num].u = u;
    edge[edge_num].v = v;
    edge[edge_num].r = rate;
    edge[edge_num].c = cost;
    edge[edge_num].next = head[u];
    head[u] = edge_num;
    edge_num++;
}
int main() {
//    freopen("in.txt", "r", stdin);
    edge_num = 0;
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%lf", &n, &m, &source, &original);
    for (int i = 1; i <= m; i++) {
        int a, b;
        double r1, c1, r2, c2;
        scanf("%d%d%lf%lf%lf%lf", &a, &b, &r1, &c1, &r2, &c2);
        addEdge(a, b, r1, c1);
        addEdge(b, a, r2, c2);
    }
    if (spfa()) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
    return 0;
}
