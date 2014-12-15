#include <cstdio>
#include <cstring>
#include <vector>

const int maxn = 100007;
using namespace std;

vector<int> path[maxn];
vector<int> ans;
int low[maxn], high[maxn], cnt_depth;
bool init[maxn], goal[maxn];
bool tree[2][maxn], vis[maxn];
bool d[maxn];
int n, ans_number;
int lowbit(int x) {
    return x & (-x);
}

bool sums(int depth, int x) {
    int ret = 0;
    while (x > 0) {
        ret ^= tree[depth][x];
        x -= lowbit(x);
    }
    return ret;
}

void add(int depth, int x, int val) {
    while (x <= n) {
        tree[depth][x] ^= val;
        x += lowbit(x);
    }
}

void dfs(int cnt_point) {
    low[cnt_point] = ++cnt_depth;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!vis[next_point]) {
            vis[next_point] = 1;
            d[next_point] = d[cnt_point] ^ 1;
            dfs(next_point);
        }
    }
    high[cnt_point] = cnt_depth;
}

void dfs2(int cnt_point) {
    bool fix = sums(d[cnt_point], low[cnt_point]);
    fix = fix ^ init[cnt_point];
    if (fix != goal[cnt_point]) {
        ans.push_back(cnt_point);
        add(d[cnt_point], low[cnt_point], 1);
        add(d[cnt_point], high[cnt_point] + 1, 1);
        for (int i = 0; i < path[cnt_point].size(); i++) {
            int next_point = path[cnt_point][i];
            if (!vis[next_point]) {
                vis[next_point] = 1;
                dfs2(next_point);
            }
        }
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    cnt_depth = 0;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(b);
        path[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        int flag;
        scanf("%d", &flag);
        init[i] = flag;
    }
    for (int i = 1; i <= n; i++) {
        int flag;
        scanf("%d", &flag);
        goal[i] = flag;
    }
    memset(tree, 0, sizeof(tree));
    memset(vis, 0, sizeof(vis));
    memset(d, 0, sizeof(d));
    vis[1] = 1;
    dfs(1);
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            dfs2(i);
        }
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
