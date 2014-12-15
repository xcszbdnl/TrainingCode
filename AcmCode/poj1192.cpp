#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

const int MAX_NUMBER = 1006;

using namespace std;

struct Point {
    int x, y;
    int value;
};

struct Point point[MAX_NUMBER];
vector<int> path[MAX_NUMBER];
int dp[MAX_NUMBER], vis[MAX_NUMBER];
int point_number;

bool check(int i, int j) {
    int temp1 = point[i].x - point[j].x;
    int temp2 = point[i].y - point[j].y;
    if (abs(temp1) + abs(temp2) == 1) {
        return 1;
    }
    return 0;
}

void dfs(int cnt_point) {
    dp[cnt_point] = point[cnt_point].value;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!vis[next_point]) {
            vis[next_point] = 1;
            dfs(next_point);
            if (dp[next_point] > 0) {
                dp[cnt_point] += dp[next_point];
            }
        }
    }
}

int main() {

    while (scanf("%d", &point_number) != EOF) {
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= point_number; i++) {
            path[i].clear();
        }
        for (int i = 1; i <= point_number; i++) {
            scanf("%d%d%d", &point[i].x, &point[i].y, &point[i].value);
        }
        for (int i = 1; i <= point_number; i++) {
            for (int j = i + 1; j <= point_number; j++) {
                if (check(i, j)) {
                    path[i].push_back(j);
                    path[j].push_back(i);
                }
            }
        }
        for (int i = 1; i <= point_number; i++) {
            if (!vis[i]) {
                vis[i] = 1;
                dfs(i);
            }
        }
        int max_number = 0;
        for (int i = 1; i <= point_number; i++) {
            if (dp[i] > max_number) {
                max_number = dp[i];
            }
        }
        printf("%d\n", max_number);
    }
    return 0;
}
