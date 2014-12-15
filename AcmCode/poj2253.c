#include <stdio.h>
#include <string.h>
#include <cmath>


#define MAX_NUMBER 250
#define INF 100000

struct Point {
    int x;
    int y;
};

struct Point point[MAX_NUMBER];

int point_number;
double edge[MAX_NUMBER][MAX_NUMBER];
double distance[MAX_NUMBER];
int vis[MAX_NUMBER];

double calculateDistance(int i, int j) {
    double x_plus = point[i].x - point[j].x;
    double y_plus = point[i].y - point[j].y;
    double two_distance = x_plus * x_plus + y_plus * y_plus;
    two_distance = sqrt(two_distance);
    return two_distance;
}

double max(double x, double y) {
    if (x > y) {
        return x;
    }
    else {
        return y;
    }
}

void dijkstra() {
    int i, j, current_point, next_point;
    double min_distance; 
    memset(vis, 0, sizeof(vis));
    for (i = 0; i < point_number; i++) {
        distance[i] = INF;
    }
    distance[0] = 0;
    current_point = 0;
    for (j = 0; j < point_number; j++) {
        min_distance = INF;
        for (i = 1; i < point_number; i++) {
            if (!vis[i]) {
                if (distance[i] > max(distance[current_point], edge[i][current_point])) {
                    distance[i] = max(distance[current_point], edge[i][current_point]);
                }
                if (min_distance > distance[i] ) {
                    min_distance = distance[i];
                    next_point = i;
                }
            }
        }
        if (next_point == 1) {
            return ;
        }
        current_point = next_point;
        vis[current_point] = 1;
    }
}

int main() {

    int i, j, case_number;
    double edge_distance;
    case_number = 1;
    while (scanf("%d", &point_number) != EOF) {
        if (!point_number) {
            break;
        }
        for (i = 0; i < point_number; i++) {
            scanf("%d%d", &point[i].x, &point[i].y);
            for (j = i - 1; j >= 0; j--) {
                edge_distance = calculateDistance(i, j);
                edge[i][j] = edge[j][i] = edge_distance;
            }
        }
        dijkstra();
        printf("Scenario #%d\n", case_number);
        printf("Frog Distance = %.3f\n\n", distance[1]);
        case_number++;
    }
    return 0;
}
