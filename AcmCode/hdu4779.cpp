#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
const int maxn = 200007;

struct Q {
    int l, r, idx;
    bool operator <(const struct Q &a) const {
        return  r < a.r;
    }
};
struct Q q[maxn];
vector<int> pos[maxn];
vector<int> divisor[maxn];
int l[maxn], r[maxn], val[maxn], prime[maxn], vis[maxn], prime_num, p[maxn], ans[maxn];
int n, m;

void init() {
    for (int i = 2; i <= sqrt(maxn); i++) {
        if (!vis[i]) {
            for (int j = i * 2; j < maxn; j += i) {
                vis[j] = 1;
            }
        }
    }
    prime_num = 0;
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) {
            prime[++prime_num] = i;
        }
    }
    for (int i = 2; i < maxn; i++) {
        int temp = i;
        for (int j = 1; j <= prime_num && prime[j] * prime[j] <= i; j++) {
            if (temp % prime[j] == 0) {
                divisor[i].push_back(prime[j]);
                while (temp % prime[j] == 0) {
                    temp /= prime[j];
                }
            }
        }
        if (temp != 1) {
            divisor[i].push_back(temp);
        }
    }
}

int tree[maxn];
int lowbit(int x) {
    return x & (-x);
}
void add(int x, int val) {
    if (x == 0) {
        return ;
    }
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
int main() {
//    freopen("in.txt", "r", stdin);
    init();
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(tree, 0, sizeof(tree));
        for (int i = 1; i <= n; i++) {
            pos[i].clear();
            scanf("%d", &val[i]);
        }
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].idx = i;
        }
        sort(q + 1, q + 1 + m);
        memset(p, 0, sizeof(p));
        for (int i = 1; i <= n; i++) {
            int temp = val[i];
            l[i] = 0;
            for (int j = 0; j < divisor[temp].size(); j++) {
                l[i] = max(l[i], p[divisor[temp][j]]);
                p[divisor[temp][j]] = i;
            }
        }
        memset(p, 0x7f, sizeof(p));
        for (int i = n; i >= 1; i--) {
            r[i] = n + 1;
            int temp = val[i];
            for (int j = 0; j < divisor[temp].size(); j++) {
                r[i] = min(r[i], p[divisor[temp][j]]);
                p[divisor[temp][j]] = i;
            }
        }
        for (int i = 1; i <= n; i++) {
            pos[r[i]].push_back(i);
        }
        int cnt = 1;
        for (int i = 1; i <= m; i++) {
            while (cnt <= n && cnt <= q[i].r) {
                add(l[cnt], 1);
                for (int j = 0; j < pos[cnt].size(); j++) {
                    int v = pos[cnt][j];
                    add(l[v], -1);
                    add(v, 1);
                }
                cnt++;
            }
            ans[q[i].idx] = sum(q[i].r) - sum(q[i].l - 1);
            ans[q[i].idx] = q[i].r - q[i].l + 1 - ans[q[i].idx];
        }
        for (int i = 1; i <= m; i++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
