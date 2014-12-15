#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 105;

int maps[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER][MAX_NUMBER];
int row, column;

void dfs(int cnt_x, int cnt_y) {
    if (vis[cnt_x][cnt_y] || !maps[cnt_x][cnt_y]) {
        return ;
    }
    vis[cnt_x][cnt_y] = 1;
    dfs(cnt_x - 1, cnt_y - 1);
    dfs(cnt_x - 1, cnt_y);
    dfs(cnt_x - 1, cnt_y + 1);
    dfs(cnt_x, cnt_y - 1);
    dfs(cnt_x, cnt_y + 1);
    dfs(cnt_x + 1, cnt_y - 1);
    dfs(cnt_x + 1, cnt_y);
    dfs(cnt_x + 1, cnt_y + 1);
}

int main() {

    scanf("%d%d", &row, &column);
    memset(maps, 0, sizeof(maps));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= row; i++) {
        char input[MAX_NUMBER];
        scanf("%s", input);
        for (int j = 0; input[j]; j++) {
            if (input[j] == '.') {
                maps[i][j + 1] = 0;
            }
            else {
                maps[i][j + 1] = 1;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= column; j++) {
            if (!vis[i][j] && maps[i][j]) {
                dfs(i, j);
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
