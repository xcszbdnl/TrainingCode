#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;
const int maxn = 55;
const long long mod = 55566677;
struct Q {
    int d, c;
};

struct Q q[maxn];
int maps[maxn][maxn], vis_c[maxn], vis_d[maxn];
int n, m, len;
long long val[maxn], ans;

void dfs(int cnt, int num) {
    if (cnt == len) {
        if (num % 2) {
            ans = (ans - val[n - num]) % mod;
        }
        else {
            ans = (ans + val[n - num]) % mod;
        }
        return ;
    }
    dfs(cnt + 1, num);
    if (!vis_c[q[cnt].c] && !vis_d[q[cnt].d]) {
        vis_c[q[cnt].c] = vis_d[q[cnt].d] = 1;
        dfs(cnt + 1, num + 1);
        vis_c[q[cnt].c] = vis_d[q[cnt].d] = 0;
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    val[0] = 1;
    for (int i = 1; i < maxn; i++) {
        val[i] = (val[i - 1] * i) % mod;
    }
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(maps, 0, sizeof(maps));
        memset(vis_c, 0, sizeof(vis_c));
        memset(vis_d, 0, sizeof(vis_d));
        len = 0;
        ans = 0;
        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (!maps[a][b]) {
                maps[a][b] = 1;
                q[len].d = a;
                q[len].c = b;
                len++;
            }
        }
        dfs(0, 0);
        ans = ans % mod;
        ans = (ans + mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
