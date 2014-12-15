#include <string.h>
#include <cstdio>
#include <vector>
#include <algorithm>


using namespace std;
const int MAX_NUMBER = 10005;

vector<int> path[MAX_NUMBER];
vector<int> children[MAX_NUMBER];
int dp[MAX_NUMBER], vis[MAX_NUMBER], ans[MAX_NUMBER], flag[MAX_NUMBER];
int point_number, ans_number;

void dfs(int cnt_point) {
    dp[cnt_point] = 1;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!vis[next_point]) {
            vis[next_point] = 1;
            dfs(next_point);
            dp[cnt_point] = dp[cnt_point] + dp[next_point];
            if (dp[next_point] > (point_number / 2)) {
                flag[cnt_point] = 1;
            }
        }
    }
    if ((point_number - dp[cnt_point]) > (point_number / 2)) {
        flag[cnt_point] = 1;
    }
}

int main() {

    scanf("%d", &point_number);
    for (int i = 1; i <= point_number - 1; i++) {
        int start, end;
        scanf("%d%d", &start, &end);
        path[start].push_back(end);
        path[end].push_back(start);
    }
    memset(vis, 0, sizeof(vis));
    memset(dp, 0, sizeof(0));
    memset(ans, 0, sizeof(ans));
    memset(flag, 0, sizeof(flag));
    ans_number = 0;
    vis[1] = 1;
    dfs(1);
    for (int i = 1; i <= point_number; i++) {
        if (!flag[i]) {
            ans[ans_number++] = i;
        }
    }
    if (ans_number != 0) {
        for (int i = 0; i < ans_number; i++) {
            printf("%d\n", ans[i]);
        }
    }
    else {
        printf("NONE\n");
    }
    return 0;
}





