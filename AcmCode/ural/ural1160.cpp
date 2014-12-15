#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;


const int maxn = 20007;
struct Edge {
    int u, v, cost;
    bool operator < (const struct Edge &a) const {
        return cost < a.cost;
    }
};

struct Edge edge[maxn];
int fa[maxn], n, m, use[maxn];

int findFa(int x) {
    if (x == fa[x]) {
        return x;
    }
    return fa[x] = findFa(fa[x]);
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].cost);
    }
    sort(edge + 1, edge + 1 + m);
    memset(use, 0, sizeof(use));
    int max_ans = 0;
    for (int i = 1; i <= m; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        int x = findFa(u);
        int y = findFa(v);
        if (x != y) {
            fa[x] = y;
            use[i] = 1;
            max_ans = max(max_ans, edge[i].cost);
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (use[i]) {
            ans++;
        }
    }
    printf("%d\n%d\n", max_ans, ans);
    for (int i = 1; i <= m; i++) {
        if (!use[i]) {
            continue;
        }
        printf("%d %d\n", edge[i].u, edge[i].v);
    }
    return 0;
}
