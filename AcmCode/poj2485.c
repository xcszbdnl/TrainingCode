#include <string.h>
#include <stdio.h>

#define MAX_POINT 502
#define INF 100000

int distance[MAX_POINT][MAX_POINT];
int vis[MAX_POINT], lowest[MAX_POINT];
int point_number;

int prim() {
    int min, i, j;
    int currenct_point, max_distance;
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= point_number; i++) {
        lowest[i] = distance[1][i];
    }
    vis[1] = 1;
    max_distance = 0;
    for (i = 1; i < point_number; i++) {
        min = INF;
        for (j = 1; j <= point_number; j++) {
            if (!vis[j] && min > lowest[j]) {
                min = lowest[j];
                currenct_point = j;
            }
        }
        vis[currenct_point] = j;
        if (lowest[currenct_point] > max_distance) {
            max_distance = lowest[currenct_point];
        }
        for (j = 1; j <= point_number; j++) {
            if (!vis[j] && lowest[j] > distance[currenct_point][j]) {
                lowest[j] = distance[currenct_point][j];
            }
        }
    }
    return max_distance;
}

int main() {

    int i, j, test_case, two_distance;
    int max_distance;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &point_number);
        for (i = 1; i <= point_number; i++) {
            for (j = 1; j <= point_number; j++) {
                scanf("%d", &two_distance);
                distance[i][j] = distance[j][i] = two_distance;
            }
        }
        max_distance = prim();
        printf("%d\n", max_distance);
    }
    
}
