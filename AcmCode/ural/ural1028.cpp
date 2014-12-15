#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 35007;

struct Point {
    int x, y;
};
struct Point point[maxn];
int tree[maxn], ans[maxn];

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int val) {
    while (x < maxn) {
        tree[x] += val;
        x += lowbit(x);
    }
}

bool cmp(struct Point a, struct Point b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}
int sums(int x) {
    int ret = 0;
    while (x > 0) {
        ret += tree[x];
        x -= lowbit(x);
    }
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x++;
        y++;
        point[i].x = x;
        point[i].y = y;
    }
    sort(point + 1, point + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        int a = sums(point[i].y);
        ans[a]++;
        add(point[i].y, 1);
    }
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
