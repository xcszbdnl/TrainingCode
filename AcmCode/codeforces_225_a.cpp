#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_NUMBER = 200007;

vector<int> path[MAX_NUMBER];
int low[MAX_NUMBER], high[MAX_NUMBER], value[MAX_NUMBER], depth[MAX_NUMBER], vis[MAX_NUMBER], number;
int tree_array[2][MAX_NUMBER], n, m;

int lowbit(int x) {
    return x & (-x);
}
int sums(int s, int x) {
    int ret = 0;
    while (x) {
        ret += tree_array[s][x];
        x -= lowbit(x);
    }
    return ret;
}

int add(int s, int x, int d) {
    while (x <= n) {
        tree_array[s][x] += d;
        x += lowbit(x);
    }
}

void dfs(int cnt) {
    low[cnt] = ++number;
    for (int i = 0; i < path[cnt].size(); i++) {
        int next = path[cnt][i];
        if (!vis[next]) {
            depth[next] = depth[cnt] + 1;
            vis[next] = 1;
            dfs(next);
        }
    }
    high[cnt] = number;
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &value[i]);
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(b);
        path[b].push_back(a);
    }
    number = 0;
    vis[1] = 1;
    dfs(1);
    for (int i = 1; i <= m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int x, val;
            scanf("%d%d", &x, &val);
            add(depth[x] % 2, low[x], val);
            add(depth[x] % 2, high[x] + 1, -val);
            add((depth[x] + 1) % 2, low[x], -val);
            add((depth[x] + 1) % 2, high[x] + 1, val);
        }
        else {
            int x;
            scanf("%d", &x);
            int ans = sums(depth[x] % 2, low[x]);
            printf("%d\n", ans + value[x]);
        }
    }
    return 0;
}
