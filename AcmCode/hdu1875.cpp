#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string.h>

#define MAX_NUMBER 105
#define INF 10000000
using namespace std;

struct Point {
    int x;
    int y;
};

struct Point point[MAX_NUMBER];
int point_number;
double maps[MAX_NUMBER][MAX_NUMBER];
double lowest[MAX_NUMBER];
double ans;
int vis[MAX_NUMBER];


double getDistance(struct Point point_1, struct Point point_2) {
    int square_x = (point_1.x - point_2.x) * (point_1.x - point_2.x);
    int square_y = (point_1.y - point_2.y) * (point_1.y - point_2.y);
    double result = square_x + square_y;
    return sqrt(result);
}

int prim() {
    int i, j, cnt_point;
    double min_distance;
    for(i = 1; i <= point_number; i++) {
        lowest[i] = maps[1][i];
    }
    vis[1] = 1;
    for (i = 1; i < point_number; i++) {
        min_distance = INF;
        for (j = 1; j <= point_number; j++) {
            if (!vis[j] && lowest[j] < min_distance && lowest[j] >= 10.0000 && lowest[j] <= 1000.0000) {
                cnt_point = j;
                min_distance = lowest[j];
            }
        }
        if (min_distance == INF) {
            return -1;
        }
        vis[cnt_point] = 1;
        ans += min_distance;
        for (j = 1; j <= point_number; j++) {
            if (!vis[j] && lowest[j] > maps[cnt_point][j]) {
                lowest[j] = maps[cnt_point][j];
            }
        }
    }
    return 1;
}

int main() {

    int test_case, flag, i, j;
    double distance;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &point_number);
        memset(maps, 0, sizeof(maps));
        memset(vis, 0, sizeof(vis));
        ans = 0;
        for (i = 1; i <= point_number; i++) {
            scanf("%d%d", &point[i].x, &point[i].y);
        }
        for (i = 1; i <= point_number; i++) {
            for (j = 1; j <= point_number; j++) {
                maps[i][j] = INF;
            }
        }
        for (i = 1; i <= point_number; i++) {
            for (j = i + 1; j <= point_number; j++) {
                distance = getDistance(point[i], point[j]);
                maps[i][j] = maps[j][i] = distance;
            }
        }
        flag = prim();
        if (flag == -1) {
            printf("oh!\n");
        }
        else {
            printf("%.1lf\n", ans * 100);
        }
    }
}
