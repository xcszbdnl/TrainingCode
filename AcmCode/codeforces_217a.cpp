#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_NUMBER = 105;

struct Point {
    int x, y;
};

struct Point point[MAX_NUMBER];
vector<int> path[MAX_NUMBER];
int vis[MAX_NUMBER];
int point_number;

void dfs(int cnt_point) {
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!vis[next_point]) {
            vis[next_point] = 1;
            dfs(next_point);
        }
    }
}

int main() {

    scanf("%d", &point_number);
    for (int i = 1; i <= point_number; i++) {
        scanf("%d%d", &point[i].x, &point[i].y);
    }
    int result = 0;
    for (int i = 1; i <= point_number; i++) {
        for (int j = i + 1; j <= point_number; j++) {
            if (point[i].x == point[j].x || point[i].y == point[j].y) {
                path[i].push_back(j);
                path[j].push_back(i);
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= point_number; i++) {
        if (!vis[i]) {
            result++;
            vis[i] = 1;
            dfs(i);
        }
    }
    printf("%d\n", result - 1);
    return 0;
}
