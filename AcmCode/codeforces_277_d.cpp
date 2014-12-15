#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int maxn = 2007;
const long long mod = 1e9 + 7;

using namespace std;

vector<int> path[maxn];
int d, n, val[maxn];
long long ans;

long long dfs(int cnt, int fa, int k) {
    long long ret = 1;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (v == fa) {
            continue;
        }
        if (val[v] > val[k] + d || val[v] < val[k]) {
            continue;
        }
        if (val[v] == val[k] && v < k) {
            continue;
        }
        long long temp = dfs(v, cnt, k);
        ret = ret * (temp + 1) % mod;
    }
    return ret;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &d, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(b);
        path[b].push_back(a);
    }
    ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + dfs(i, i, i)) % mod;
    }
    printf("%I64d\n", ans);
    return 0;
}
