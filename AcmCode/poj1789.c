#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 2005
#define INF 2000

int vis[MAX_NUMBER];
int distance[MAX_NUMBER][MAX_NUMBER];
int lowest[MAX_NUMBER];
int truck_types;
char truck_code[MAX_NUMBER][7];

int prim() {
    int sums, i, j;
    int min, currenct_point;
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= truck_types; i++) {
        lowest[i] = distance[1][i];
    }
    vis[1] = 1;
    lowest[1] = INF;
    sums = 0;
    for (i = 1; i < truck_types; i++) {
        min = INF;
        for (j = 1; j <= truck_types; j++) {
            if (!vis[j] && lowest[j] < min) {
                min = lowest[j];
                currenct_point = j;
            }
        }
        vis[currenct_point] = 1;
        sums += lowest[currenct_point];
        for (j = 1; j <= truck_types; j++) {
            if (!vis[j] && distance[currenct_point][j] < lowest[j]) {
                lowest[j] = distance[currenct_point][j];
            }
        }
    }
    return sums;
}

int main() {

    int i, j, k;
    int difference, mst_sum;
    while (scanf("%d", &truck_types) != EOF) {
        if (!truck_types) {
            break;
        }
        for (i = 1; i <= truck_types; i++) {
            scanf("%s", truck_code[i]);
            for (j = i -1; j >= 1; j--) {
                difference = 0;
                for (k = 0; k < 7; k++) {
                    if (truck_code[i][k] != truck_code[j][k]) {
                        difference++;
                    }
                }
                distance[i][j] = distance[j][i] = difference;
            }
        }
        mst_sum = prim();
        printf("The highest possible quality is 1/%d.\n", mst_sum);
    }
}
