#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100007;
int n;

struct D{
    int a, b;
};

struct D d[maxn];
int tree[maxn];

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int val) {
    while (x <= n) {
        tree[x] += val;
        x += lowbit(x);
    }
}

int sum(int x) {
    int ret = 0;
    while (x > 0) {
        ret += tree[x];
        x -= lowbit(x);
    }
    return ret;
}

bool cmp(struct D a, struct D b) {
    return a.a < b.a;
}
int main() {
//    freopen("in.txt", "r", stdin);
    memset(tree, 0, sizeof(tree));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &d[i].a, &d[i].b);
    }
    sort(d + 1, d + 1 + n, cmp);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int flag = sum(n) - sum(d[i].b);
        if (flag >= 1) {
            ans = 1;
            break;
        }
        add(d[i].b, 1);
    }
    if (ans) {
        printf("Happy Alex\n");
    }
    else {
        printf("Poor Alex\n");
    }
    return 0;
}
