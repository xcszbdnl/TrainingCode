#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>


const int maxn = 1007;
using namespace std;
int n, m, k;
vector<int> path[maxn];
int vis[maxn], pre[maxn];

int dfs(int cnt) {
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (!vis[v]) {
            vis[v] = 1;
            if (!pre[v] || dfs(pre[v])) {
                pre[v] = cnt;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(b);
    }
    memset(pre, 0, sizeof(pre));
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) {
            ans++;
        }
    }
    printf("%d\n", n + m - ans);
    return 0;
}
