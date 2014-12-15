#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 105
#define INF 1000000

int distance[MAX_NUMBER][MAX_NUMBER];
int lowest[MAX_NUMBER], vis[MAX_NUMBER];
int point_number;


int prim() {
    int i, sum, min, j;
    int currenct_point;
    sum = 0;
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= point_number; i++) {
        lowest[i] = distance[1][i];
    }
    vis[1] = 1;
    for (i = 1; i < point_number; i++) {
        min = INF;
        for (j = 1; j <= point_number; j++) {
            if (!vis[j] && lowest[j] < min) {
                min = lowest[j];
                currenct_point = j;
            }
        }
        vis[currenct_point] = 1;
        sum += lowest[currenct_point];

        for (j = 1; j <= point_number; j++) {
            if (!vis[j] && lowest[j] > distance[currenct_point][j]) {
                lowest[j] = distance[currenct_point][j];
            }
        }
    }
    return sum;
}


int main() {

    int i, j;
    int two_distance, sum;
    while (scanf("%d", &point_number) != EOF) {
        if (!point_number) {
            break;
        }
        for (i = 1; i <= point_number; i++) {
            for (j = 1; j <= point_number; j++) {
                scanf("%d", &two_distance);
                distance[i][j] = distance[j][i] = two_distance;
            }
        }
        sum = prim();
        printf("%d\n", sum);
    }
}
