#include <stdio.h>
#include <string.h>

#define MAX_POINT 200
#define MAX_EDGE 200000
#define SUPER_SOURCE 200
#define INF 1000000

struct Edge {
    int start;
    int end;
    int value;
};


struct Edge edge[MAX_EDGE];
int distance[MAX_POINT];
int edge_number, point_number, constraint;

void addEdge(int start, int end, int value) {
    edge[edge_number].start = start;
    edge[edge_number].end = end;
    edge[edge_number].value = value;
    edge_number++;
}

int bellmanFord() {
    int i, k, flag, start, end, value;
    for (i = 0; i <= point_number; i++) {
        distance[i] = INF;
    }
    distance[0] = 0;
    for (i = 1; i <= point_number ; i++) {
        flag = 1;
        for (k = 0; k < edge_number; k++) {
            start = edge[k].start;
            end = edge[k].end;
            if (distance[start] != INF && distance[end] > distance[start] + edge[k].value) {
                distance[end] = distance[start] + edge[k].value;
                flag = 0;
            }
        }
        if (flag) {
            break;
        }
    }
    for (k = 0; k < edge_number; k++) {
        start = edge[k].start;
        end = edge[k].end;
        if (distance[end] > distance[start] + edge[k].value) {
            return 0;
        }
    }
    return 1;
}


int main() {

    int i, start, end, value;
    char symbol[10];
    while (scanf("%d", &point_number) != EOF) {
        if (!point_number) {
            break;
        }
        edge_number = 0;
        scanf("%d", &constraint);
        for (i = 0; i < constraint; i++) {
            scanf("%d%d%s%d", &start, &end, symbol, &value);
            if (symbol[0] == 'g') {
                addEdge(start + end, start - 1, -value - 1);
            }
            else {
                addEdge(start - 1, start + end, value - 1);
            }
        }
        for (i = 0; i <= point_number; i++) {
            addEdge(SUPER_SOURCE, i, 0);
        }
        if (bellmanFord()) {
            printf("lamentable kingdom\n");
        }
        else {
            printf("successful conspiracy\n");
        }
    }
    return 0;
}
