#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 207;
vector<int> path[maxn];
vector<int> ans;
queue<int> que;
int n, color[maxn], vis[maxn];


void dfs(int cnt) {
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (!vis[v]) {
            vis[v] = 1;
            color[v] = 1 - color[cnt];
            dfs(v);
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    memset(vis, 0, sizeof(vis));
    memset(color, 0, sizeof(color));
    for (int i = 1; i <= n; i++) {
        while (1) {
            int a;
            scanf("%d", &a);
            if (!a) {
                break;
            }
            path[i].push_back(a);
        }
    }
    int flag = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (path[i].size() == 0) {
                flag = 1;
                break;
            }
            vis[i] = 1;
            color[i] = 1;
            dfs(i);
        }
    }
    if (flag) {
        printf("0\n");
    }
    else {
        ans.clear();
        for (int i = 1; i <= n; i++) {
            if (color[i]) {
                ans.push_back(i);
            }
        }
        printf("%d\n", ans.size());
        for (int i = 0; i < ans.size(); i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
