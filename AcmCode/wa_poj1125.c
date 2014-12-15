#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 105
#define INF 100


int edge[MAX_NUMBER][MAX_NUMBER];
int point_number, max_point, latest_time;
int vis[MAX_NUMBER];
int distance[MAX_NUMBER];

void prim() {
    int i, k, min_distance, next_point;
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= point_number; i++) {
        distance[i] = edge[1][i];
    }
    vis[1] = 1;
    distance[1] = INF;
    for (i = 0; i < point_number; i++) {
        min_distance = INF;
        for (k = 1; k <= point_number; k++) {
            if (!vis[k] && distance[k] < min_distance) {
                min_distance = distance[k];
                next_point = k;
            }
        }
        vis[next_point] = 1;
        if (distance[next_point] > max_point) {
            latest_time = distance[next_point];
            max_point = next_point;
        }

        for (k = 1; k <= point_number; k++) {
            if (!vis[k] && edge[next_point] != -1 && distance[k] > edge[next_point][k]) {
                distance[k] = edge[next_point][k];
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int i, k, end_point, time, pairs;
    while (scanf("%d", &point_number) != EOF) {
        memset(edge, -1, sizeof(edge));
        for (i = 1; i <= point_number; i++) {
            scanf("%d", &pairs);
            for (k = 0; k < pairs; k++) {
                scanf("%d%d", &end_point, &time);
                edge[i][end_point] = time;
            }
        }
        prim();
        printf("%d %d\n", max_point, latest_time);
    }
}


