#include <stdio.h>
#include <string.h>


#define MAX_EDGE 20005
#define MAX_POINT 1005
#define INF 10000007


int distance[MAX_POINT];
int vis[MAX_POINT];
int map[MAX_POINT][MAX_POINT], destination, point_number;

void dijkstra() {
    int i, j, cnt_point, min_distance;
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= point_number; i++) {
        distance[i] = map[destination][i];
    }
    distance[destination] = 0;
    vis[destination] = 1;
    for (i = 1; i < point_number; i++) {
        min_distance = INF;
        for (j = 1; j <= point_number; j++) {
            if (!vis[j] && distance[j] < min_distance) {
                cnt_point = j;
                min_distance = distance[j];
            }
        }
        if (min_distance == INF) {
            break;
        }
        vis[cnt_point] = 1;
        for (j = 1; j <= point_number; j++) {
            if (!vis[j] && distance[j] > distance[cnt_point] + map[cnt_point][j]) {
                distance[j] = distance[cnt_point] + map[cnt_point][j];
            }
        }
    }
}

int main() {

    int edge_number, source_number, i, j;
    int start, end, value;
    int min_time;
    while (scanf("%d%d%d", &point_number, &edge_number, &destination) != EOF) {
        min_time = INF;
        for (i = 1; i <= point_number; i++) {
            for (j = 1; j <= point_number; j++) {
                map[i][j] = INF;
            }
        }
        for (i = 0; i < edge_number; i++) {
            scanf("%d%d%d", &start, &end, &value);
            if (value < map[end][start]) {
                map[end][start] = value;
            }
        }
        dijkstra();        
        scanf("%d", &source_number);
        for (i = 0; i < source_number; i++) {
            scanf("%d", &start);
            if (min_time > distance[start]) {
                min_time = distance[start];
            }
        }
        if (min_time == INF) {
            printf("-1\n");
        }
        else {
            printf("%d\n", min_time);
        }
    }
    return 0;
}
