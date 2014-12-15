#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define mp(a,b) make_pair(a,b)

using namespace std;

const int maxn = 10007;

vector<pair<int, int> >path[maxn];
int vis[maxn], depth[maxn], siz[maxn];
int root, root_max, tot_size, n;
int query[maxn], query_num, ans[maxn];
vector<int> dist;

void dfs(int cnt, int fa) {
    siz[cnt] = 1;
    int max_son = 0;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i].first;
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


void getDist(int cnt, int fa) {
    dist.push_back(depth[cnt]);
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i].first;
        if (!vis[v] && v != fa) {
            depth[v] = depth[cnt] + path[cnt][i].second;
            getDist(v, cnt);
        }
    }
}

void cal(int cnt, int d, int flag) {
    depth[cnt] = d;
    dist.clear();
    getDist(cnt, 0);
    sort(dist.begin(), dist.end());
    for (int i = 1; i <= query_num; i++) {
        for (int l = 0; l < dist.size(); l++) {
            int p = query[i] - dist[l];
            int loc_1 = lower_bound(dist.begin(), dist.end(), p) - dist.begin();
            int loc_2 = upper_bound(dist.begin(), dist.end(), p) - dist.begin();
            ans[i] += flag * (loc_2 - loc_1);
        }
    }
}

void work(int cnt) {
    cal(cnt, 0, 1);
    vis[cnt] = 1;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i].first;
        if (!vis[v]) {
            cal(v, path[cnt][i].second, -1);
            tot_size = root_max = root = siz[v];
            dfs(v, 0);
            work(root);
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        if (!n) {
            break;
        }
        for (int i = 1; i <= n; i++) {
            path[i].clear();
        }
        memset(vis, 0, sizeof(vis));
        memset(depth, 0, sizeof(depth));
        memset(siz, 0, sizeof(siz));
        memset(ans, 0, sizeof(ans));
        query_num = 0;
        for (int i = 1; i <= n; i++) {
            while (1) {
                int a;
                scanf("%d", &a);
                if (!a) {
                    break;
                }
                int b;
                scanf("%d", &b);
                path[i].push_back(mp(a,b));
                path[a].push_back(mp(i,b));
            }
        }
        while (1) {
            int a;
            scanf("%d", &a);
            if (!a) {
                break;
            }
            query[++query_num] = a;
        }
        tot_size = root = root_max = n;
        dfs(1, 0);
        work(root);
        for (int i = 1; i <= query_num; i++) {
            if(ans[i] > 0) {
                printf("AYE\n");
            }
            else {
                printf("NAY\n");
            }
        }
        printf(".\n");
    }
    return 0;
}
