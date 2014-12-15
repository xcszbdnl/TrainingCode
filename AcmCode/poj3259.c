#include <stdio.h>
#include <string.h>


#define MAX_EDGE 10000
#define MAX_POINT 600
#define INF 100000

struct Edge {
    int start_point;
    int end_point;
    int time;
};

struct Edge edge[MAX_EDGE];
int distance[MAX_POINT];
int edge_number, point_number;

int bellmanFord() {
    int i, k, flag;
    int start_point, end_point;
    for (i = 1; i < point_number; i++) {
        distance[i] = INF;
    }
    distance[0] = 0;
    for (i = 0; i < point_number; i++) {
        flag = 0;
        for (k = 0; k < edge_number; k++) {
            start_point = edge[k].start_point;
            end_point = edge[k].end_point;
            if (distance[start_point] != INF && distance[end_point] > distance[start_point] + edge[k].time) {
                distance[end_point] = distance[start_point] + edge[k].time;
                flag = 1;
            }
        }
        if (!flag) {
            break;
        }
    }
    for (i = 0; i < edge_number; i++) {
        start_point = edge[i].start_point;
        end_point = edge[i].end_point;
        if (distance[end_point] > distance[start_point] + edge[i].time) {
            return 0;
        }
    }
    return 1;
}


int main() {

    int farm_number, i, path_number, wormhole_number;
    int start_point, end_point, time;
    scanf("%d", &farm_number);
    while (farm_number--) {
        edge_number = 0;
        scanf("%d%d%d", &point_number, &path_number, &wormhole_number);
        for (i = 0; i < path_number; i++) {
            scanf("%d%d%d", &start_point, &end_point, &time);
            edge[edge_number].start_point = start_point;
            edge[edge_number].end_point = end_point;
            edge[edge_number].time = time;
            edge_number++;

            edge[edge_number].start_point = end_point;
            edge[edge_number].end_point = start_point;
            edge[edge_number].time = time;
            edge_number++;
        }

        for (i = 0; i < wormhole_number; i++) {
            scanf("%d%d%d", &start_point, &end_point, &time);
            edge[edge_number].start_point = start_point;
            edge[edge_number].end_point = end_point;
            edge[edge_number].time = -time;
            edge_number++;
        }
        if (bellmanFord()) {
            printf("NO\n");
        }
        else {
            printf("YES\n");
        }
    }
    return 0;
}
