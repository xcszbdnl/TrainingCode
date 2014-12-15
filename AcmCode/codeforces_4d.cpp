#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_NUMBER = 5006;
struct Point {
    int w, h;
};

struct Point point[MAX_NUMBER];
vector<short> path[MAX_NUMBER];
int vis[MAX_NUMBER], degree[MAX_NUMBER], dp[MAX_NUMBER], father[MAX_NUMBER], order[MAX_NUMBER];
int w, h, point_number;

void dfs(int cnt_point) {
    if (dp[cnt_point] != -1) {
        return ;
    }
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        dfs(next_point);
        if (dp[next_point] + 1 > dp[cnt_point]) {
            dp[cnt_point] = dp[next_point] + 1;
            father[cnt_point] = next_point;
        }
    }
}
int first;
void printPath(int cnt_point) {
    if (cnt_point != -1) {
        printPath(father[cnt_point]);
        if (first) {
            printf("%d", order[cnt_point]);
            first = 0;
        }
        else {
            printf(" %d", order[cnt_point]);
        }
    }
}

int main() {

    int temp_point;
    first = 1;
    scanf("%d%d%d", &temp_point, &w, &h);
    point_number = 0;
    for (int i = 1; i <= temp_point; i++) {
        int temp_w, temp_h;
        scanf("%d%d", &temp_w, &temp_h);
        if (temp_w > w && temp_h > h) {
            point_number++;
            point[point_number].w = temp_w;
            point[point_number].h = temp_h;
            order[point_number] = i;
        }
    }
    if (point_number == 0) {
        printf("0\n");
        return 0;
    }
    memset(degree, 0, sizeof(degree));
    for (int i = 1; i <= point_number; i++) {
        for (int j = i + 1; j <= point_number; j++) {
            if (point[i].w > point[j].w && point[i].h > point[j].h) {
                path[i].push_back(j);
                degree[i]++;
            }
            if (point[j].w > point[i].w && point[j].h > point[i].h) {
                path[j].push_back(i);
                degree[j]++;
            }
        }
    }
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= point_number; i++) {
        if (degree[i] == 0) {
            dp[i] = 1;
            father[i] = -1;
        }
    }
    for (int i = 1; i <= point_number; i++) {
        dfs(i);
    }
    int max_number = 0;
    int ans;
    for (int i = 1; i <= point_number; i++) {
        if (dp[i] > max_number) {
            max_number = dp[i];
            ans = i;
        }
    }
    printf("%d\n", max_number);
    printPath(ans);
    printf("\n");
    return 0;
}
