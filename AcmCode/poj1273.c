#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 203
#define INF 1000000000

int cap[MAX_NUMBER][MAX_NUMBER];
int flow[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER], queue[MAX_NUMBER * 10];
int father[MAX_NUMBER];

int edge_number, point_number;

int edmondsKarp() {
    int source = 1, destination = point_number;
    int front, rear, max_value, last_point, cnt_point, i;
    max_value = 0;
    while (1) {
        memset(vis, 0, sizeof(vis));
        front = 0;
        rear = 1;
        queue[front] = source;
        vis[source] = INF;
        while (front < rear) {
            cnt_point = queue[front];
            for (i = 1; i <= point_number; i++) {
                if (!vis[i] && cap[cnt_point][i] > flow[cnt_point][i]) {
                    father[i] = cnt_point;
                    queue[rear++] = i;
                    if (cap[cnt_point][i] - flow[cnt_point][i] < vis[cnt_point]) {
                        vis[i] = cap[cnt_point][i] - flow[cnt_point][i];
                    }
                    else {
                        vis[i] = vis[cnt_point];
                    }
                }
            }
            front++;
        }
        if (vis[destination] == 0) {
            break;
        }
        for (last_point = destination; last_point != source; last_point = father[last_point]) {
            flow[father[last_point]][last_point] += vis[destination];
            flow[last_point][father[last_point]] -= vis[destination];
        }
        max_value += vis[destination];
    }
    return max_value;
}

int main() {

    int i, start, end, value, max_value;
    while (scanf("%d%d", &edge_number, &point_number) != EOF) {
        memset(cap, 0, sizeof(cap));
        memset(flow, 0, sizeof(flow));
        for (i = 0; i < edge_number; i++) {
            scanf("%d%d%d", &start, &end, &value);
            cap[start][end] += value;
        }
        max_value = edmondsKarp();
        printf("%d\n", max_value);
    }
    return 0;
}
