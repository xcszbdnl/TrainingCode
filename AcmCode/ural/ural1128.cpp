#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
const int maxn = 7200;
int n, flag;
int color[maxn], vis[maxn];
vector<int> path[maxn];
vector<int> degree[maxn];
queue<int> que;
stack<int> sta;
void bfs(int p) {
    que.push(p);
    while (!que.empty()) {
        int cnt = que.front();
        que.pop();
        for (int i = 0; i < path[cnt].size(); i++) {
            int v = path[cnt][i];
            if (!vis[v]) {
                vis[v] = 1;
                color[v] = 1 - color[cnt];
                que.push(v);
            }
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        degree[k].push_back(i);
        for (int j = 1; j <= k; j++) {
            int a;
            scanf("%d", &a);
            path[i].push_back(a);
        }
    }
    memset(vis, 0, sizeof(vis));
    memset(color, 0, sizeof(color));
    flag = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            bfs(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
        int num = 0;
        for (int j = 0; j < path[i].size(); j++) {
            int v = path[i][j];
            if (color[v] == color[i]) {
                num++;
            }
        }
        if (num >= 2) {
            color[i] ^= 1;
        }
    }
    int time = 0;
//    while (!sta.empty()) {
//        int cnt = sta.top();
//        sta.pop();
//        int num = 0;
//        for (int i = 0; i < path[cnt].size(); i++) {
//            int v = path[cnt][i];
//            if (color[v] == color[cnt]) {
//                num++;
//            }
//        }
//        if (num <= 1) {
//            continue;
//        }
//        color[cnt] = 1 - color[cnt];
//        vis[cnt] = 1;
//        time++;
//        if (time > n) {
//            flag = 1;
//            break;
//        }
//        for (int i = 0; i < path[cnt].size(); i++) {
//            int v = path[cnt][i];
//            int num = 0;
//            for (int j = 0; j < path[v].size(); j++) {
//                int another = path[v][j];
//                if (!vis[another] && color[another] == color[v]) {
//                    num++;
//                }
//            }
//            if (num >= 2) {
//                sta.push(v);
//            }
//        }
//    }
    if (flag) {
        printf("NO SOLUTION\n");
        return 0;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            ans++;
        }
    }
    int ans_color = 0;
    if (ans > n - ans) {
        ans = n - ans;
        ans_color ^= 1;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) {
        if (color[i] == ans_color) {
            printf("%d%c", i, i == n ? '\n' : ' ');
        }
    }
//    printf("\n");
    return 0;
}
