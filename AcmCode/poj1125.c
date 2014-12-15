#include <stdio.h>
#include <string.h>

#define INF 2000
#define MAX_NUMBER 105

int distance[MAX_NUMBER][MAX_NUMBER];
int point_number;

void floyd() {
    int i, j, k;
    for (k = 1; k <= point_number; k++) {
        for (i = 1; i <= point_number; i++) {
            for (j = 1; j <= point_number; j++) {
                if (distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

int main() {

    int i, j, pairs, time, contract, latest_time, max, source;
    while (scanf("%d", &point_number) != EOF) {
        if (!point_number) {
            break;
        }
        for (i = 1; i <= point_number; i++) {
            for (j = 1; j <= point_number; j++) {
                if (i != j) {
                    distance[i][j] = INF;
                }
                else {
                    distance[i][j] = 0;
                }
            }
            scanf("%d", &pairs);            
            for (j = 0; j < pairs; j++) {
                scanf("%d%d", &contract, &time);
                distance[i][contract] = time;
            }
        }
        floyd();
        latest_time = INF;
        for (i = 1; i <= point_number; i++) {
            max = 0;
            for (j = 1; j <= point_number; j++) {
                if (distance[i][j] > max) {
                    max = distance[i][j];
                }
            }
            if (max < latest_time) {
                latest_time = max;
                source = i;
            }
        }
        if (latest_time == INF) {
            printf("disjoint\n");
        }
        else {
            printf("%d %d\n", source, latest_time);
        }
    }
    return 0;
}
