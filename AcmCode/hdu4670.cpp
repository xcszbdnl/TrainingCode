#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
const int maxn = 50007;
int prime[maxn], prime_num;
int vis[maxn], n, siz[maxn];
int num[maxn][32], tmp_num[maxn][32];
int n, root, root_max, tot_size;

map<long long, int> maps;
map<long long, int>::iterator *it;
vector<int> path[maxn];
long long ans;

void dfs(int cnt, int fa) {
    siz[cnt] = 1;
    int max_son = 0;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (!vis[v] && v != fa) {
            dfs(v, cnt);
            siz[cnt] += siz[v];
            max_son = max(max_son, siz[v]);
        }
    }
    if (max_son < tot_size - siz[cnt]) {
        max_son = tot_size - siz[cnt];
    }
    if (max_son < root_max) {
        root_max = max_son;
        root = cnt;
    }
}


int cal(int cnt) {
    int ret = 0;
    maps.clear();
    getVal(cnt);
    for (it = maps.begin(); it != end; it++) {

    }
}
void work(int cnt) {
    vis[cnt] = 1;
    ans += cal(cnt);
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (!vis[v]) {
            memcpy(tmp_num[v], num[cnt], sizeof(num[cnt]));
            ans -= cal(v);
            root_max = root = tot_size = siz[v];
            dfs(v, 0);
            work(v);
        }
    }
}
int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        memset(vis, 0, sizeof(vis));
        memset(num, 0, sizeof(num));
        memset(siz, 0, sizeof(siz));
        for (int i = 1; i <= n; i++) {
            path[i].clear();
        }
        int k;
        scanf("%d", &k);
        for (int i = 1; i <= k; i++) {
            scanf("%d", &prime[i]);
        }
        for (int i = 1; i <= n; i++) {
            long long tmp;
            scanf("%I64d", &tmp);
            for (int j = 1; j <= k; j++) {
                int cnt = 0;
                while (tmp % prime[j]) {
                    cnt++;
                    tmp /= prime[j];
                }
                cnt %= 3;
                num[i][j] = cnt;
            }
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            path[a].push_back(b);
            path[b].push_back(a);
        }
        root = root_max = tot_size = n;
        dfs(1, 0);
        cal(root);
        printf("%I64d\n", ans);
    }
    return 0;
}
