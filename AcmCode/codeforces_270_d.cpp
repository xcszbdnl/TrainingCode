#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>


const int maxn = 2007;

using namespace std;
int maps[maxn][maxn], vis[maxn][maxn], vis_1[maxn];
int n, edge_num, flag, fa[maxn];

struct Edge {
    int u, v, c;
};

struct Edge edge[maxn * maxn];

vector<pair<int, int> > path[maxn];

int findFa(int x) {
    return x == fa[x] ? x : fa[x] = findFa(fa[x]);
}

void dfs(int cnt, int cnt_fa, int root, int cnt_dist) {
    vis_1[cnt] = 1;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i].first;
        int c = path[cnt][i].second;
        if (v != cnt_fa) {
            if (cnt_dist + c != maps[root][v]) {
                flag = 1;
                return ;
            }
            dfs(v, cnt, root, cnt_dist + c);
        }
    }
}


bool cmp(struct Edge a, struct Edge b) {
    return a.c < b.c;
}
int main() {
//    freopen("in.txt", "r", stdin);
    memset(vis, 0, sizeof(vis));
    memset(maps, 0, sizeof(maps));
    edge_num  = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &maps[i][j]);
        }
    }
    flag = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        if (maps[i][i] != 0) {
            flag = 1;
            break;
        }
        for (int j = i + 1; j <= n; j++) {
            if (maps[i][j] != maps[j][i]) {
                flag = 1;
                break;
            }
        }
    }
    if (flag) {
        printf("NO\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            edge[edge_num].u = i;
            edge[edge_num].v = j;
            edge[edge_num].c = maps[i][j];
            if (maps[i][j] != 0) {
                edge_num++;
            }
        }
    }
    sort(edge, edge + edge_num, cmp);
    int num = 0;
    for (int i = 0; i < edge_num; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        int x = findFa(u);
        int y = findFa(v);
        if (x == y) {
            continue;
        }
        path[u].push_back(make_pair(v, edge[i].c));
        path[v].push_back(make_pair(u, edge[i].c));
        fa[x] = y;
        num++;
    }
    if (num != n - 1) {
        printf("NO\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        dfs(i, i, i, 0);
    }
    if (!flag) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
    return 0;
}
