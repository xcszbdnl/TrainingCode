#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 400

struct Edge {
    int start_point;
    int end_point;
    double commission;
    double rate;
};

struct Edge edge[MAX_NUMBER];
int original_currency, point_number, currency_number;
int edge_number;
double distance[MAX_NUMBER];
double original_money;
    
int bellmanFord() {
    int flag, i;
    int start_point, end_point;
    double temp_money;
    memset(distance, 0 ,sizeof(distance));
    distance[original_currency] = original_money;
    while (distance[original_currency] <= original_money) {
        flag = 0;
        for (i = 0; i < edge_number; i++) {
            start_point = edge[i].start_point;
            end_point = edge[i].end_point;
            temp_money = (distance[start_point] - edge[i].commission) * edge[i].rate;
            if (distance[end_point] < temp_money) {
                distance[end_point] = temp_money;
                flag = 1;
            }
        }
        if (!flag) {
            return distance[original_currency] > original_money;
        }
    }
    return 1;
}

int main() {

    int start_point, end_point, i;
    double rate_a, commission_a, rate_b, commission_b;
    while (scanf("%d%d%d%lf", &currency_number, &point_number, &original_currency, &original_money) != EOF) {
        edge_number = 0;
        for (i = 0; i < point_number; i++) {
            scanf("%d%d%lf%lf%lf%lf", &start_point, &end_point, &rate_a, &commission_a, &rate_b, &commission_b);
            edge[edge_number].start_point = start_point;
            edge[edge_number].end_point = end_point;
            edge[edge_number].rate = rate_a;
            edge[edge_number].commission = commission_a;
            edge_number++;

            edge[edge_number].start_point = end_point;
            edge[edge_number].end_point = start_point;
            edge[edge_number].rate = rate_b;
            edge[edge_number].commission = commission_b;
            edge_number++;
        }
        if (bellmanFord()) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
}
