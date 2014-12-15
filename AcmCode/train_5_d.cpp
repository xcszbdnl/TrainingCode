#include <cstdio>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_POINT = 505;
const int INF = 10000000;

struct Edge {
    int start;
    int end;
    double value;
};

struct Point {
    int x;
    int y;
};

struct Point point[MAX_POINT];
struct Edge edge[MAX_POINT];
int vis[MAX_POINT], pre[MAX_POINT];
double maps[MAX_POINT][MAX_POINT], lowest[MAX_POINT], cost[MAX_POINT];
double ans;
int point_number, satellite_number, edge_number;

double getLength(Point a, Point b) {
    double x = a.x - b.x;
    x = x * x;
    double y = a.y - b.y;
    y = y * y;
    return sqrt(x + y);
}

bool cmp(Edge a, Edge b) {
    return a.value > b.value;
}


void prime() {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= point_number; i++) {
        lowest[i] = maps[1][i];
        pre[i] = 1;
    }
    vis[1] = 1;
    for (int i = 1; i < point_number; i++) {
        double min_ans = INF;
        int next_point;
        for (int j = 1; j <= point_number; j++) {
            if (!vis[j] && lowest[j] < min_ans) {
                min_ans = lowest[j];
                next_point = j;
            }
        }
        vis[next_point] = 1;
        cost[i] = min_ans;
        for (int j = 1; j <= point_number; j++) {
            if (!vis[j] && lowest[j] > maps[next_point][j]) {
                lowest[j] = maps[next_point][j];
                pre[j] = next_point;
            }
        }
    }
    sort(cost + 1, cost + point_number);
}

int main() {

    int test_case;
    scanf("%d", &test_case);
    while(test_case--) {
        edge_number = 0;
        memset(maps, 0, sizeof(maps));
        scanf("%d%d", &satellite_number, &point_number);
        for (int i = 1; i <= point_number; i++) {
            scanf("%d%d", &point[i].x, &point[i].y);
        }
        for (int i = 1; i <= point_number; i++) {
            for (int j = i + 1; j <= point_number; j++) {
                double length = getLength(point[i], point[j]);
                maps[i][j] = maps[j][i] = length;
            }
        }
        edge_number = 0;
        prime();
        ans = cost[point_number - satellite_number];
        printf("%.2lf\n", ans);
    }
}
