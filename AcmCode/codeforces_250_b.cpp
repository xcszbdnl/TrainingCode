#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 100007;
int val[maxn];
struct Point {
    int a, b, val;
};
struct Point edge[maxn];
vector<int> path[maxn];
int n, m;
int father[maxn], num[maxn], vis[maxn];
double ans;
bool cmp(struct Point a, struct Point b) {
    return a.val > b.val;
}

int find(int x) {
    if (x == father[x]) {
        return x;
    }
    else {
        father[x] = find(father[x]);
        return father[x];
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        num[i] = 1;
        scanf("%d", &val[i]);
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        edge[i].a = a;
        edge[i].b = b;
        edge[i].val = min(val[a], val[b]);
    }
    ans = 0;
    sort(edge + 1, edge + 1 + m, cmp);
    for (int i = 1; i <= m; i++) {
        int x = find(edge[i].a);
        int y = find(edge[i].b);
        if (x == y) {
            continue;
        }
        ans += 1.0 * num[x] * num[y] * edge[i].val;
//        printf("%d %d %d %d %d\n", edge[i].a, edge[i].b, num[x], num[y], edge[i].val);
        father[x] = y;
        num[y] += num[x];
    }
//    printf("%lf\n", ans);
    ans = ans * 2;
    ans = ans / n / (n - 1);
    printf("%.4lf\n", ans);
    return 0;
}
