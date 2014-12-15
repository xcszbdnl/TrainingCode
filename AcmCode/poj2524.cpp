#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 50008;

vector<int> path[maxn];
int n, m, vis[maxn];

void dfs(int cnt) {
    for (int i = 0; i < path[cnt].size(); i++) {
        int next = path[cnt][i];
        if (!vis[next]) {
            vis[next] = 1;
            dfs(next);
        }
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    int ncase = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        ncase++;
        if (!m && !n) {
            break;
        }
        int ans = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++) {
            path[i].clear();
        }
        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            path[a].push_back(b);
            path[b].push_back(a);
        }
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                vis[i] = 1;
                ans++;
                dfs(i);
            }
        }
        printf("Case %d: %d\n", ncase, ans);
    }
    return 0;
}
