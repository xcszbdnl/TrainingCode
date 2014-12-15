#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 106;
const int INF = 10000007;
int maps[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER];
int point_number, last_start, last_end;
int min_ans, first;

void dfs(int cnt_point, int final_point, int ans) {
    if (cnt_point == final_point) {
        if (min_ans > ans) {
            min_ans = ans;
        }
        return ;
    }
    vis[cnt_point] = 1;
    int flag = 0;
    for (int i = 1; i <= point_number && !flag; i++) {
        if (maps[cnt_point][i] && !vis[i]) {
            flag = 1;
            dfs(i, final_point, ans);
        }
    }
    if (!flag) {
        for (int i = 1; i <= point_number && !flag; i++) {
            if (maps[i][cnt_point] && !(cnt_point == last_end && i == last_start) && !vis[i]) {
                flag = 1;
                dfs(i, final_point, ans + maps[i][cnt_point]);
            }
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &point_number);
    for (int i = 1; i <= point_number; i++) {
        int start, end, cost;
        scanf("%d%d%d", &start, &end, &cost);
        maps[start][end] = cost;
        last_start = start;
        last_end = end;
    }
    min_ans = INF;
    memset(vis, 0, sizeof(vis));
    first = 1;
    dfs(last_end, last_start, 0);
    first = 1;
    memset(vis, 0, sizeof(vis));
    maps[last_end][last_start] = maps[last_start][last_end];
    maps[last_start][last_end] = 0;
    int temp = last_start;
    last_start = last_end;
    last_end = temp;
    dfs(last_end, last_start, maps[last_start][last_end]);
    printf("%d\n", min_ans);
    return 0;
}
