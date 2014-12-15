#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 350
#define MAX_EDGE 20000
#define MAX_LENTH 500

struct Edge {
    int start_point;
    int end_point;
    double rate;
};


struct Edge edge[MAX_EDGE];
int currency_number, edge_number;
char currency_name[MAX_NUMBER][MAX_LENTH];
double distance[MAX_NUMBER];

int bellmanFord() {
    int flag, start_point, end_point;
    int i;
    double temp;
    for (i = 0; i < currency_number; i++) {
        distance[i] = 0.0;
    }
    distance[0] = 1.0;
    while (distance[0] <= 1.0) {
        flag = 0;
        for (i = 0; i < edge_number; i++) {
            start_point = edge[i].start_point;
            end_point = edge[i].end_point;
            temp = distance[start_point] * edge[i].rate;
            if (distance[end_point] < temp) {
                distance[end_point] = temp;
                flag = 1;
            }
        }
        if (!flag) {
            return distance[0] > 1.0;
        }
    }
    return 1;
}

int main() {

    int case_number = 1;
    int i, k;
    char input_line[MAX_LENTH];
    double rate;
    while (scanf("%d", &currency_number)) {
        if (!currency_number) {
            break;
        }
        for (i = 0; i < currency_number; i++) {
            scanf("%s", currency_name[i]);
        }
        scanf("%d", &edge_number);
        for (i = 0; i < edge_number; i++) {
            scanf("%s", input_line);
            for (k = 0; k < currency_number; k++) {
                if (strcmp(input_line, currency_name[k]) == 0) {
                    break;
                }
            }
            edge[i].start_point = k;
            scanf("%lf", &rate);
            edge[i].rate = rate;
            scanf("%s", input_line);
            for (k = 0; k < currency_number; k++) {
                if (strcmp(input_line, currency_name[k]) == 0) {
                    break;
                }
            }
            edge[i].end_point = k;
        }
        if (bellmanFord()) {
            printf("Case %d: Yes\n", case_number);
        }
        else {
            printf("Case %d: No\n", case_number);
        }
        case_number++;
    }
    return 0;
}
