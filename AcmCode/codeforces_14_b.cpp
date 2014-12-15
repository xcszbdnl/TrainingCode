#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 10007;
struct Edge {
    int start, end;
};
vector<int> path[maxn];
struct Edge edge[maxn];
int n, vis[maxn], max_depth, point_1, point_2, depth_point, temp[maxn];

void dfs(int cnt, int cnt_depth) {
    if (cnt_depth > max_depth) {
        max_depth = cnt_depth;
        depth_point = cnt;
    }
    for (int i = 0; i < path[cnt].size(); i++) {
        int next = path[cnt][i];
        if (!vis[next] && !(cnt == point_1 && next == point_2) && !(cnt == point_2 && next == point_1)) {
            vis[next] = 1;
            dfs(next, cnt_depth + 1);
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        edge[i].start = a;
        edge[i].end = b;
        path[a].push_back(b);
        path[b].push_back(a);
    }
    int ans = 0;
    for (int i = 1; i < n; i++) {
        int first = 1;
        int num = 0;
        point_1 = edge[i].start;
        point_2 = edge[i].end;
        memset(vis, 0, sizeof(vis));
        int cnt[2];
        for (int j = 1; j <= n; j++) {
            if (!vis[j]) {
                if (first) {
                    depth_point = 0;
                    max_depth = 0;
                    vis[j] = 1;
                    dfs(j, 0);
                    memset(vis, 0, sizeof(vis));
                    vis[depth_point] = 1;
                    max_depth = 0;
                    dfs(depth_point, 0);
                    first = 0;
                    cnt[0] = max_depth;
                }
                else if (num == 1) {
                    depth_point = 0;
                    max_depth = 0;
                    vis[j] = 1;
                    memcpy(temp, vis, sizeof(vis));
                    dfs(j, 0);
                    memset(vis, 0, sizeof(vis));
                    vis[depth_point] = 1;
                    max_depth = 0;
                    dfs(depth_point, 0);
                    cnt[1] = max_depth;
                    for (int i = 1; i <= n; i++) {
                        if (temp[i]) {
                            vis[i] = 1;
                        }
                    }
                }
                num++;
            }
        }
        if (num == 2 && cnt[0] * cnt[1] > ans) {
            ans = cnt[0] * cnt[1];
        }
    }
    printf("%d\n", ans);
    return 0;
}
