#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int maxn = 100007;
const int mod_num = 1000000 + 3;
int vis[maxn],  siz[maxn], idx[maxn], hash_num[mod_num + 10], node_num[mod_num + 10];
long long node_value[maxn], mul[maxn], inv[mod_num + 10], tmp[maxn];
vector<int> path[maxn];
int n, root, root_max, tot_size, top, time;
long long k;
map<long long, int> maps;
pair<int, int> ans;

void updateAns(int a, int b) {
    if (a > b) {
        swap(a,b);
    }
    if (ans.first > a || (ans.first == a && ans.second > b)) {
        ans.first = a;
        ans.second = b;
    }
}
void dfs(int cnt, int fa) {
    int max_son = 0;
    siz[cnt] = 1;
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

void mulDfs(int cnt, int fa) {
    mul[cnt] = (mul[fa] * node_value[cnt]) % mod_num;
    tmp[top++] = mul[cnt];
    idx[top - 1] = cnt;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (!vis[v] && v != fa) {
            mulDfs(v, cnt);
        }
    }
}
void cal(int cnt) {
    mul[cnt] = 1;
    vis[cnt] = 1;
    time++;
    for (int i = 0; i < path[cnt].size(); i++) {
        top = 0;
        int v = path[cnt][i];
        if (vis[v]) {
            continue;
        }
        mulDfs(v, cnt);
        for (int i = 0; i < top; i++) {
            if ((node_value[cnt] * tmp[i]) % mod_num == k) {
                updateAns(idx[i], cnt);
            }
            long long s = (((inv[node_value[cnt]] * inv[tmp[i]]) % mod_num) * k) % mod_num;
            if (hash_num[s] == time) {
                updateAns(idx[i], node_num[s]);
            }
        }
        for (int i = 0; i < top; i++) {
            if (hash_num[tmp[i]] != time) {
                hash_num[tmp[i]] = time;
                node_num[tmp[i]] = idx[i];
            }
            else {
                if (node_num[tmp[i]] > idx[i]) {
                    node_num[tmp[i]] = idx[i];
                }
            }
        }
    }
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (!vis[v]) {
            root_max = root = tot_size = siz[v];
            dfs(v, 0);
            cal(root);
        }
    }
}

long long power(long long a, int b) {
    long long ret = 1;
    while (b) {
        if (b & 1) {
            ret = (ret * a) % mod_num;
        }
        a = (a * a) % mod_num;
        b /= 2;
    }
    return ret;
}
int main() {
//    freopen("in.txt", "r", stdin);
    for (int i = 1; i <= mod_num; i++) {
        inv[i] = power(i, mod_num - 2);
    }
    while (scanf("%d%I64d", &n, &k) != EOF) {
        memset(vis, 0, sizeof(vis));
        memset(siz, 0, sizeof(siz));
        memset(hash_num, 0, sizeof(hash_num));
        time = 0;
        for (int i = 1; i <= n; i++) {
            path[i].clear();
        }
        for (int i = 1; i <= n; i++) {
            scanf("%I64d", &node_value[i]);
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            path[a].push_back(b);
            path[b].push_back(a);
        }
        ans.first = maxn;
        ans.second = maxn;
        root = root_max = tot_size = n;
        dfs(1, 0);
        cal(root);
        if (ans.first == maxn) {
            printf("No solution\n");
        }
        else {
            printf("%d %d\n", ans.first, ans.second);
        }
    }
    return 0;
}
