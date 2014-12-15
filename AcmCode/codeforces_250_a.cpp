#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 3000;
struct Point {
    int val, order;
};
struct Point point[maxn];
int vis[maxn], val[maxn];
vector<int> path[maxn];
int n, m;

bool cmp(struct Point a, struct Point b) {
    return a.val > b.val;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &point[i].val);
        val[i] = point[i].val;
        point[i].order = i;
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(b);
        path[b].push_back(a);
    }
    memset(vis, 0, sizeof(vis));
    sort(point + 1, point + 1 + n, cmp);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int cnt_order = point[i].order;
        for (int j = 0; j < path[cnt_order].size(); j++) {
            int next_point = path[cnt_order][j];
            if (!vis[next_point]) {
                ans += val[next_point];
            }
        }
        vis[cnt_order] = 1;
    }
    printf("%d\n", ans);
    return 0;
}
