#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 10007;
const int INF = 1000007;
vector<int> path[maxn], ans;
int temp_depth, vis[maxn];

void dfs(int cnt, int depth) {
    if (temp_depth < depth) {
        temp_depth = depth;
    }
    for (int i = 0; i < path[cnt].size(); i++) {
        int next = path[cnt][i];
        if (!vis[next]) {
            vis[next] = 1;
            dfs(next, depth + 1);
        }
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int father;
        scanf("%d", &father);
        path[father].push_back(i);
        path[i].push_back(father);
    }
    int min_depth = INF;
    for (int i = 1; i <= n; i++) {
        temp_depth = 0;
        memset(vis, 0, sizeof(vis));
        vis[i] = 1;
        dfs(i, 0);
        if (temp_depth < min_depth) {
            min_depth = temp_depth;
            ans.clear();
            ans.push_back(i);
        }
        else if (temp_depth == min_depth) {
            ans.push_back(i);
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
