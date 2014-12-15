#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 30


int map[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER];
int m, n, step;
char ans[MAX_NUMBER];

int dfs(int start, int cur) {
    int i, flag;
    ans[cur] = start + 'A';
    if (cur == n - 1) {
        step = cur + 1;
        return 1;
    }
    vis[start] = 1;
    for (i = 0; i < n; i++) {
        if (map[start][i]) {
            if (vis[i]) {
                step = cur + 1;
                return 2;
            }
            else {
                flag = dfs(i, cur + 1);
                if (flag == 1 || flag == 2) {
                    return flag;
                }
                else {
                    continue;
                }
            }
        }
    }
    vis[start] = 0;
    return 0;
}

int main() {

    int i, start_point, end_point, success;
    char relation[MAX_NUMBER];
    while (scanf("%d%d", &n, &m) != EOF) {
        if (!m && !n) {
            break;
        }
        memset(vis, 0, sizeof(vis));
        memset(map, 0, sizeof(map));
        for (i = 0; i < m; i++) {
            scanf("%s", relation);
            if (relation[1] == '>') {
                start_point = relation[2] - 'A';
                end_point = relation[0] - 'A';
                map[start_point][end_point] = 1;
            }
            else {
                start_point = relation[0] - 'A';
                end_point = relation[2] - 'A';
                map[start_point][end_point] = 1;
            }
        }
        for (i = 0; i < n; i++) {
            success = dfs(i, 0);
            if (success == 1) {
                printf("Sorted sequence determined after %d relations: %s.\n", step, ans);
                break;
            }
            else if (success == 2) {
                printf("Inconsistency found after %d relations.\n", step);
                break;
            }
        }
        if (i == n) {
            printf("Sorted sequence cannot be determined.\n");
        }
    }
}
