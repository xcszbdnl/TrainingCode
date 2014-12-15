#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 50007;
vector<pair<int, int> > path[maxn];
int vis[maxn], depth[maxn], max_depth, father[maxn][20], dist[maxn];
int n, q;

void dfs(int u, int cnt_depth) {
    depth[u] = cnt_depth;
    for (int i = 0; i < path[u].size(); i++) {
        int v = path[u][i].first;
        if (!vis[v]) {
            vis[v] = 1;
            dist[v] = dist[u] + path[u][i].second;
            father[v][0] = u;
            dfs(v, cnt_depth + 1);
        }
    }
}
void getAnc() {
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i <= n; i++) {
            if (father[i][j - 1] != -1) {
                father[i][j] = father[father[i][j - 1]][j - 1];
            }
        }
    }
}
int lca(int x, int y) {
    if (depth[x] < depth[y]) {
        int temp = x;
        x = y;
        y = temp;
    }
    int k = depth[x] - depth[y];
    for (int i = 0; i <= 16; i++) {
        if ((1 << i) & k) {
            x = father[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 16; i >= 0; i--) {
        if (father[x][i] != father[y][i]) {
            x = father[x][i];
            y = father[y][i];
        }
    }
    return father[x][0];
}

int main() {
//    freopen("in.txt", "r", stdin);
    memset(dist, 0, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        path[a].push_back(make_pair(b, c));
        path[b].push_back(make_pair(a, c));
    }
    father[0][0] = -1;
    dfs(0, 0);
    getAnc();
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        int x = lca(a, b);
        printf("%d\n", dist[a] + dist[b] - 2 * dist[x]);
    }
    return 0;
}
