#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn =107;

char maps[maxn][maxn];

int n, m;
char color[10];
int vis[maxn], min_x, min_y, max_x, max_y;

int main() {
//    freopen("in.txt", "r", stdin);
    memset(vis,0, sizeof(vis));
    scanf("%d%d%s", &n, &m, color);
    min_x = maxn, min_y = maxn, max_x = 0, max_y = 0;
    for (int i = 0; i < n; i++) {
        scanf("%s", maps[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maps[i][j] == color[0]) {
                min_x = min(min_x, i);
                min_y = min(min_y, j);
                max_x = max(max_x, i);
                max_y = max(max_y, j);
            }
        }
    }
    int ans = 0;
//    printf("%d %d %d %d\n", min_x, max_x, min_y, max_y);
    int dot = '.' - 'A';
    if (min_y >= 1) {
        for (int i = min_x; i <= max_x; i++) {
            int idx = maps[i][min_y - 1] - 'A';
            if (idx != dot && !vis[idx]) {
                vis[idx] = 1;
                ans++;
            }
        }
    }
    if (min_x >= 1) {
        for (int i = min_y; i <= max_y; i++) {
            int idx = maps[min_x - 1][i] - 'A';
            if (idx != dot && !vis[idx]) {
                vis[idx] = 1;
                ans++;
            }
        }
    }
    if (max_y <= m - 2) {
        for (int i = min_x; i <= max_x; i++) {
            int idx = maps[i][max_y + 1] - 'A';
            if (idx != dot && !vis[idx]) {
                vis[idx] = 1;
                ans++;
            }
        }
    }
    if (max_x <= n - 2) {
        for (int i = min_y; i <= max_y; i++) {
            int idx = maps[max_x + 1][i] - 'A';
            if (idx != dot && !vis[idx]) {
                vis[idx] = 1;
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
