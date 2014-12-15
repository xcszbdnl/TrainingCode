#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_NUMBER 105
#define INF 1000

int cap[MAX_NUMBER][MAX_NUMBER];
int flow[MAX_NUMBER][MAX_NUMBER];
int father[MAX_NUMBER];
int state[MAX_NUMBER];
int queue[MAX_NUMBER];

int point_number, station_number, consumer_number, edge_number;

int edmondsKarp(int source, int destination) {
    int final_flow = 0;
    int front, rear, current_point, last_point, previous_point;
    int i;
    while (1) {
        memset(state, 0, sizeof(state));
        front = 0;
        rear = 1;
        queue[0] = source;
        state[source] = INF;
        while (front < rear) {
            current_point = queue[front];
            for (i = 0; i <= point_number + 1; i++) {
                if (!state[i] && cap[current_point][i] > flow[current_point][i]) {
                    father[i] = current_point;
                    queue[rear] = i;
                    rear++;
                    if (cap[current_point][i] - flow[current_point][i] < state[current_point]) {
                        state[i] = cap[current_point][i] - flow[current_point][i];
                    }
                    else {
                        state[i] = state[current_point];
                    }
                }
            }
            front++;
        }
        if (state[destination] == 0) {
            break;
        }
        for (last_point = destination; last_point != source; last_point = father[last_point]) {
            flow[father[last_point]][last_point] += state[destination];
            flow[last_point][father[last_point]] -= state[destination];
        }
        final_flow += state[destination];
    }
    return final_flow;
}


int main() {

    int i, j;
    int start_point, end_point, max_cap, max_flow;
    char temp, temp1, temp2, temp3;
    while (scanf("%d%d%d%d", &point_number, &station_number, &consumer_number, &edge_number) != EOF) {
        memset(cap, 0 ,sizeof(cap));
        memset(flow, 0, sizeof(flow));
        memset(father, 0, sizeof(father));
        for (i = 0; i < edge_number; i++) {
            cin >> temp >> start_point >> temp >> end_point >> temp >> max_cap;
            cap[start_point + 1][end_point + 1] = max_cap;
        }
        for (i = 0; i < station_number; i++) {
            cin >> temp >> start_point >> temp >> max_cap;
            cap[0][start_point + 1] = max_cap;
        }
        for (i = 0; i < consumer_number; i++) {
            cin >> temp >> start_point >> temp >> max_cap;
            cap[start_point + 1][point_number + 1] = max_cap;
        }
        max_flow = edmondsKarp(0, point_number + 1);
        printf("%d\n", max_flow);
    }
}
