#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 100007;
const long long mod = 1000 * 1000 * 1000 + 7;

vector<int> path[maxn];
long long dp[maxn][2];
int vis[maxn][2];
int col_num[maxn];
int n, color[maxn], fa[maxn];


void dfs(int cnt, int fa) {
    if (color[cnt]) {
        dp[cnt][1] = 1;
        dp[cnt][0] = 0;
    }
    else {
        dp[cnt][1] = 0;
        dp[cnt][0] = 1;
    }
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (v == fa) {
            continue;
        }
        dfs(v, cnt);
        dp[cnt][1] = (((dp[cnt][1] * dp[v][1]) % mod + (dp[cnt][1] * dp[v][0]) % mod) % mod + (dp[cnt][0] * dp[v][1]) % mod) % mod;
        dp[cnt][0] = ((dp[cnt][0] * dp[v][0]) % mod + (dp[cnt][0] * dp[v][1]) % mod) % mod;
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    memset(vis, 0, sizeof(vis));
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int x;
        scanf("%d", &x);
        path[i + 1].push_back(x);
        path[x].push_back(i + 1);
    }
    int num = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &color[i]);
        if (color[i]) {
            num++;
        }
    }
    if (num == 0) {
        printf("0\n");
        return 0;
    }
    dfs(0, 0);
    printf("%I64d\n", dp[0][1]);
    return 0;
}
