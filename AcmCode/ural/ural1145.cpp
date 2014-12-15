#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
const int maxn = 1000;

struct Point {
    int x, y, d;
};

queue<struct Point> que;
char maps[maxn][maxn], vis[maxn][maxn];
int n, m, max_ans;
int step[4][2] = {1,0,-1,0,0,1,0,-1};

struct Point bfs(int x, int y) {
    while (!que.empty()) {
        que.pop();
    }
    struct Point cnt;
    vis[x][y] = 1;
    cnt.x = x, cnt.y = y, cnt.d = 0;
    que.push(cnt);
    max_ans = -1;
    struct Point ret;
    while (!que.empty()) {
        cnt = que.front();
        que.pop();
        if (cnt.d > max_ans) {
            max_ans = cnt.d;
            ret = cnt;
        }
        for (int i = 0; i < 4; i++) {
            int next_x = cnt.x + step[i][0];
            int next_y = cnt.y + step[i][1];
            if (next_x >= 0 && next_x < m && next_y >= 0 && next_y < n) {
                if (!vis[next_x][next_y] && maps[next_x][next_y] == '.') {
                    vis[next_x][next_y] = 1;
                    struct Point next;
                    next.x = next_x, next.y = next_y, next.d = cnt.d + 1;
                    que.push(next);
                }
            }
        }
    }
    return ret;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", maps[i]);
    }
    int x = 0, y = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (maps[i][j] == '.') {
                x = i;
                y = j;
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    struct Point p;
    p = bfs(x, y);
    memset(vis, 0, sizeof(vis));
    p = bfs(p.x, p.y);
    printf("%d\n", p.d);
    return 0;
}
