#include <stdio.h>
#include <string.h>


#define MAX_FILM 1005
#define FILM_NUMBER 30
#define MAX_DAY 400

int map[MAX_FILM][MAX_DAY];
int previous_node[MAX_DAY];
int vis[MAX_FILM], film_number, days, finish_week, days_number;
int schedule[FILM_NUMBER][8];

int hungary(int node_number) {
    int i;
    for (i = 1; i <= days_number; i++) {
        if (map[node_number][i] && !vis[i]) {
            vis[i] = 1;
            if (!previous_node[i] || hungary(previous_node[i])) {
                previous_node[i] = node_number;
                return 1;
            }
        }
    }
    return 0;
}

int main() {

    int i, j, k, test_case, point_number, ans, flag, max_week;
    scanf("%d", &test_case);
    while (test_case--) {
        point_number = 1;
        ans = flag = max_week = 0;
        memset(map, 0, sizeof(map));
        memset(previous_node, 0, sizeof(previous_node));
        scanf("%d", &film_number);
        for (i = 1; i <= film_number; i++) {
            for (j = 1; j <= 7; j++) {
                scanf("%d", &schedule[i][j]);
            }
            scanf("%d%d", &days, &finish_week);
            if (finish_week > max_week) {
                max_week = finish_week;
                days_number = max_week * 7;
            }
            for (j = 0; j < finish_week; j++) {
                for (k = 1; k <= 7; k++) {
                    if (schedule[i][k]) {
                        map[point_number][j * 7 + k] = 1;
                    }
                }
            }
            for (j = 1; j < days; j++) {
                memcpy(map[point_number + j], map[point_number], sizeof(map[point_number]));
            }
            point_number += days;
        }
        for (i = 1; i < point_number; i++) {
            memset(vis, 0, sizeof(vis));
            if (!hungary(i)) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}
