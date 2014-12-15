#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>


using namespace std;
#define mp(a,b) make_pair(a,b)
const int maxn = 10007;

vector<pair<int, int> > path[maxn];
int siz[maxn], depth[maxn], vis[maxn];
int n, k, root, ans, root_max, tot_size;
vector<int> dist;

void getRoot(int cnt, int fa) {
    siz[cnt] = 1;
    int max_son = 0;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i].first;
        if (!vis[v] && v != fa) {
            getRoot(v, cnt);
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
int cal(int cnt, int d) {
    dist.clear();
    depth[cnt] = d;
    getDist(cnt, 0);
    sort(dist.begin(), dist.end());
    int ret = 0;
    for (int l = 0, r = dist.size() - 1; l < r; ) {
        if (dist[l] + dist[r] <= k) {
            ret += r - l;
            l++;
        }
        else {
            r--;
        }
    }
    return ret;
}



void work(int cnt) {
    ans += cal(cnt, 0);
    vis[cnt] = 1;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i].first;
        if (!vis[v]) {
            ans -= cal(v, path[cnt][i].second);
            root = 0, root_max = tot_size = siz[v];
            getRoot(v, 0);
            work(root);
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &k) != EOF) {
        if (!n && !k) {
            break;
        }
        memset(vis, 0, sizeof(vis));
        memset(depth, 0, sizeof(depth));
        ans = 0;
        for (int i = 1; i <= n; i++) {
            path[i].clear();
        }
        for (int i = 1; i <= n - 1; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            path[a].push_back(mp(b,c));
            path[b].push_back(mp(a,c));
        }
        root_max = tot_size = n;
        root = 0;
        getRoot(1, 0);
        work(root);
        printf("%d\n", ans);
    }
    return 0;
}
