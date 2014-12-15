#include <stdio.h>


#define MAX_NUMBER 300000
#define MAX_POINT 20000
#define INF 1000000000

struct Edge {
    int start_point;
    int end_point;
    int distance;
};

struct Edge edge[MAX_NUMBER];
int distance[MAX_POINT];
int edge_number, point_number;


int bellmanFord() {
    int i, k, flag;
    int start_point, end_point;
    for (i = 1; i < point_number + 1; i++) {
        distance[i] = INF;
    }
    distance[1] = 0;
    for (i = 1; i < point_number; i++) {
        flag = 0;
        for (k = 0; k < edge_number; k++) {
            start_point = edge[k].start_point;
            end_point = edge[k].end_point;
            if (distance[end_point] > distance[start_point] + edge[k].distance) {
                distance[end_point] = distance[start_point] + edge[k].distance;
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
        if (distance[end_point] != INF && distance[end_point] > distance[start_point] + edge[i].distance) {
            return 0;
        }
    }
    return 1;
}

int main() {

    int ML, MD, start_point, end_point, two_distance;
    int i;
    while (scanf("%d%d%d", &point_number, &ML, &MD) != EOF) {
        edge_number = 0;
        for (i = 0; i < ML; i++) {
            scanf("%d%d%d", &start_point, &end_point, &two_distance);
            edge[edge_number].start_point = start_point;
            edge[edge_number].end_point = end_point;
            edge[edge_number].distance = two_distance;
            edge_number++;
        }
        for (i = 0; i < MD; i++) {
            scanf("%d%d%d", &start_point, &end_point, &two_distance);
            edge[edge_number].start_point = end_point;
            edge[edge_number].end_point = start_point;
            edge[edge_number].distance = -two_distance;
            edge_number++;
        }
        
        if (!bellmanFord()) {
            printf("-1\n");
        }
        else {
            if (distance[point_number] == INF) {
                printf("-2\n");
            }
            else {
                printf("%d\n", distance[point_number]);
            }
        }
    }
    return 0;
}

