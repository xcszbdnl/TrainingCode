#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>


const int maxn = 1007;
using namespace std;

vector<int> boy_skill[maxn];
vector<int> path[maxn];
int n, m, vis[maxn], pre[maxn], ans;

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
    scanf("%d", &n);
    memset(pre, 0, sizeof(pre));
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        boy_skill[x].push_back(i);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        for (int j = -1; j <= 1 ; j++) {
            int val = x + j;
            for (int k = 0; k < boy_skill[val].size(); k++) {
                int cnt_boy = boy_skill[val][k];
                path[i].push_back(cnt_boy + m);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
