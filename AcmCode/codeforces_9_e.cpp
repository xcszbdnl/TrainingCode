#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 100;
int belong[maxn];
int vis[maxn], temp[maxn], fa[maxn];
int maps[maxn][maxn], flag;
vector<pair<int, int> >ans;
int n, m;
void dfs(int cnt, int *a) {
    for (int i = 1; i <= n && !flag; i++) {
        if (maps[cnt][i]) {
            if (i == fa[cnt]) {
                continue;
            }
            if (!vis[i]) {
                vis[i] = 1;
                fa[i] = cnt;
                dfs(i, a);
            }
            else {
                int u = cnt;
                while (u != -1) {
                    a[u]++;
                    u = fa[u];
                }
                vis[cnt] = 0;
                flag = 1;
                return ;
            }
        }
    }
}
int check() {
    memset(vis, 0, sizeof(vis));
    memset(temp, 0, sizeof(temp));
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            fa[i] = -1;
            flag = 0;
            dfs(i, temp);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (temp[i] >= 2) {
            return false;
        }
    }
    return true;
}


int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        maps[a][b] = maps[b][a] = 1;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            fa[i] = -1;
            flag = 0;
            dfs(i, belong);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (belong[i] >= 2) {
            puts("NO");
            return 0;
        }
    }
    ans.clear();
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!belong[i] && !belong[j] && !maps[i][j]) {
                maps[i][j] = maps[j][i] = 1;
                if (check()) {
                    ans.push_back(make_pair(i, j));
                }
                else {
                    maps[i][j] = maps[j][i] = 0;
                }
            }
        }
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}
