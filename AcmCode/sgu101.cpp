#include <cstdio>
#include <string.h>
#include <vector>

using namespace std;
const int MAX_NUMBER = 210;

struct Point {
    int x;
    int y;
};


struct Point point[MAX_NUMBER];
vector<int> path[MAX_NUMBER];
int vis[MAX_NUMBER], father[MAX_NUMBER];
int n, total_length, depst;

void dfs(int cnt_point, int cnt_depth) {
    if (cnt_depth > total_length) {
        total_length = cnt_depth;
        depst = cnt_point;
    }
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!vis[next_point]) {
            father[next_point] = cnt_point;
            vis[next_point] = 1;
            dfs(next_point, cnt_depth + 1);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < 2 * n; i += 2) {
        scanf("%d%d", &point[i].x, &point[i].y);
        point[i + 1].x = point[i].y;
        point[i + 1].y = point[i].x;
    }
    if (n == 1) {
        printf("1 +\n");
        return 0;
    }
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (j != (i ^ 1)) {
                if (point[i].y == point[j].x) {
                    path[i].push_back(j);
                }
            }
        }
    }
    total_length = 0;
    vis[1] = 1;
    dfs(0, 1);
    memset(father, -1, sizeof(father));
    memset(vis, 0, sizeof(vis));
    vis[depst] = 1;
    dfs(depst, 1);
    if (total_length < n) {
        memset(father, -1, sizeof(father));
        memset(vis, 0, sizeof(vis));
        dfs(1, 1);
        memset(father, -1, sizeof(father));
        memset(vis, 0, sizeof(vis));
        dfs(depst, 1);
        if (total_length < n) {
            printf("No solution\n");
        }
        else {
            for (int cnt_point = depst; cnt_point != -1; cnt_point = father[cnt_point]) {
                printf("%d", cnt_point / 2 + 1);
                if (cnt_point & 1) {
                    printf(" -\n");
                }
                else {
                    printf(" +\n");
                }
            }
        }
    }
    else {
        for (int cnt_point = father[depst]; cnt_point != -1; cnt_point = father[cnt_point]) {
            printf("%d", cnt_point / 2 + 1);
            if (cnt_point & 1) {
                printf(" -\n");
            }
            else {
                printf(" +\n");
            }
        }
    }
    return 0;
}

