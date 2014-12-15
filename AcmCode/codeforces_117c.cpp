#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 5002;


int maps[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER];
char input[MAX_NUMBER];
int ans[4], temp[4];
int flag;
int row;


void dfs(int cnt_point, int original) {
    for (int i = 1; i <= row && !flag; i++) {
        if (maps[cnt_point][i]) {
            if (maps[i][original]) {
                ans[1] = original;
                ans[2] = cnt_point;
                ans[3] = i;
                flag = 1;
            }
            else if (!vis[i]) {
                vis[i] = 1;
                dfs(i, cnt_point);
            }
        }
    }
}

int main() {

    scanf("%d", &row);
    memset(maps, 0, sizeof(maps));
    for (int i = 1; i <= row; i++) {
        scanf("%s", input);
        for (int j = 0; j < row; j++) {
            if (input[j] == '0') {
                maps[i][j + 1] =  0;
            }
            else {
                maps[i][j + 1] = 1;
            }
        }
    }
    flag = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= row && !flag; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            dfs(i, i);
        }
    }
    if (flag) {
        printf("%d %d %d\n", ans[1], ans[2], ans[3]);
    }
    else {
        printf("-1\n");
    }
    return 0;
}
