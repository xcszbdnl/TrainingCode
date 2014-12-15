#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 300007;
const int INF = 10000007;

struct Edge {
    int u, v, cost, next, order;
};

int dp[maxn], head[maxn], pre[maxn];
int n, m, edge_number;
struct Edge in[maxn];


bool cmp(struct Edge a, struct Edge b) {
    return a.cost < b.cost;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    edge_number = 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        int u, v, cost;
        scanf("%d%d%d", &u, &v, &cost);
        in[i].u = u;
        in[i].v = v;
        in[i].cost = cost;
    }
    for (int i = 1; i <= n; i++) {
        pre[i] = -1;
        dp[i] = 0;
    }
    sort(in + 1, in + 1 + m, cmp);
    for (int i = 1; i <= m; i++) {
        for (int j = i; in[j].cost == in[i].cost; j++) {

        }
    }
    int max_ans = 0;
    for (int i = 1; i <= n; i++) {
        max_ans = max(dp[i], max_ans);
    }
    printf("%d\n", max_ans);
    return 0;
}
