#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1007;
const int INF = 10000007;

char maps[maxn][12][12];
vector<pair<int, int> > result;
int vis[maxn], edge_number, n, m, k, w, father[maxn], dist[maxn], tree_map[maxn][maxn];

int getAns(int a, int b) {
    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maps[a][i][j] != maps[b][i][j]) {
                ret++;
            }
        }
    }
    return ret;
}

int prim() {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= k; i++) {
        dist[i] = tree_map[0][i];
        father[i] = 0;
    }
    vis[0] = 1;
    int ret = 0;
    for (int i = 1; i <= k; i++) {
        int min_num = INF;
        int loc = -1;
        for (int j = 1; j <= k; j++) {
            if (!vis[j] && dist[j] < min_num) {
                loc = j;
                min_num = dist[j];
            }
        }
        ret += min_num;
        vis[loc] = 1;
        result.push_back(make_pair(loc, father[loc]));
        for (int j = 1; j <= k; j++) {
            if (!vis[j] && tree_map[loc][j] < dist[j]) {
                dist[j] = tree_map[loc][j];
                father[j] = loc;
            }
        }
    }
    return ret;
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d%d%d%d", &n, &m, &k, &w);
    for (int i = 0; i <= k; i++) {
        tree_map[i][i] = 0;
        for (int j = i + 1; j <= k; j++) {
            tree_map[i][j] = tree_map[j][i] = INF;
        }
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%s", maps[i][j]);
        }
    }
    for (int i = 1; i <= k; i++) {
        for (int j = i + 1; j <= k; j++) {
            int cost = getAns(i, j);
            cost = cost * w;
            tree_map[i][j] = tree_map[j][i] = cost;
        }
        tree_map[0][i] = tree_map[i][0] = n * m;
    }
    int ans = prim();
    printf("%d\n", ans);
    for (int i = 0; i < result.size(); i++) {
        printf("%d %d\n", result[i].first, result[i].second);
    }
    return 0;
}
