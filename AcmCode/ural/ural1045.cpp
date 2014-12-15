#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_NUMBER = 1007;
vector<int> path[MAX_NUMBER];
int start, n, dp[MAX_NUMBER], vis[MAX_NUMBER];

void dfs(int cnt) {
    for (int i = 0; i < path[cnt].size(); i++) {
        int next = path[cnt][i];
        if (!vis[next]) {
            vis[next] = 1;
            dfs(next);
            if (dp[next] == 0) {
                dp[cnt] = 1;
            }
        }
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &start) != EOF) {
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            path[a].push_back(b);
            path[b].push_back(a);
        }
        vis[start] = 1;
        dfs(start);
        int flag = 0;
        int ans = MAX_NUMBER;
        for (int i = 0; i < path[start].size(); i++) {
            int next = path[start][i];
            if (dp[next] == 0) {
                flag = 1;
                if (next < ans) {
                    ans = next;
                }
            }
        }
        if (flag) {
            printf("First player wins flying to airport %d\n", ans);
        }
        else {
            printf("First player loses\n");
        }
    }
    return 0;
}
