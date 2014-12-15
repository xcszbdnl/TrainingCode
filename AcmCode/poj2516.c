#include <stdio.h>
#include <string.h>


#define MAX_EDGE 100000
#define MAX_POINT 200
#define MAX_GOODS 60
#define INF 100000
#define QUEUE_LENTH 2000


struct Edge {
    int start;
    int end;
    int cap;
    int cost;
    int next;
};

struct Edge edge[MAX_EDGE];
int head[MAX_POINT], vis[MAX_POINT], queue[MAX_POINT * 10], distance[MAX_POINT];
int orders[MAX_POINT][MAX_POINT], stored[MAX_POINT][MAX_POINT], goods_cost[MAX_GOODS][MAX_POINT][MAX_POINT];
int pre_edge[MAX_POINT];
int edge_number, place_number, shopkeeper_number, goods_number, source, destination, flow, costs;

void addEdge(int start, int end, int cap_1, int cap_2, int cost_1, int cost_2) {
    edge[edge_number].start = start;
    edge[edge_number].end = end;
    edge[edge_number].cap = cap_1;
    edge[edge_number].next = head[start];
    edge[edge_number].cost = cost_1;
    head[start] = edge_number;
    edge_number++;
    
    edge[edge_number].start = end;
    edge[edge_number].end = start;
    edge[edge_number].cap = cap_2;
    edge[edge_number].next = head[end];
    edge[edge_number].cost = cost_2;
    head[end] = edge_number;
    edge_number++;
}

int spfa() {
    int i, front, rear, cnt_point, next_point, next_edge, min_flow, top, pre_edge_number;
    for (i = 0; i <= destination; i++) {
        distance[i] = INF;
    }
    memset(vis, 0, sizeof(vis));
    distance[source] = 0;
    vis[source] = 1;
    top = 0;
    front = 0;
    rear = 1;
    queue[front] = source;
    while (front < rear) {
        cnt_point = queue[front];
        vis[cnt_point] = 1;
        for (next_edge = head[cnt_point]; next_edge != -1; next_edge = edge[next_edge].next) {
            next_point = edge[next_edge].end;
            if (edge[next_edge].cap > 0 && distance[next_point] > distance[cnt_point] + edge[next_edge].cost) {
                distance[next_point] = distance[cnt_point] + edge[next_edge].cost;
                pre_edge[next_point] = next_edge;
                if (!vis[next_point]) {
                    queue[rear] = next_point;
                    rear++;
                    rear = rear % QUEUE_LENTH;
                    vis[next_point] = 1;
                }
            }
        }
        front++;
        front = front % QUEUE_LENTH;
        vis[cnt_point] = 0;
    }
    if (distance[destination] == INF) {
        return 0;
    }
    min_flow = INF;
    for (i = destination; i != source; i = edge[pre_edge_number].start) {
        pre_edge_number = pre_edge[i];
        if (min_flow > edge[pre_edge_number].cap) {
            min_flow = edge[pre_edge_number].cap;
        }
    }
    for (i = destination; i != source; i = edge[pre_edge_number].start) {
        pre_edge_number = pre_edge[i];
        edge[pre_edge_number].cap -= min_flow;
        edge[pre_edge_number ^ 1].cap += min_flow;
        costs += edge[pre_edge_number].cost * min_flow;
    }
    flow += min_flow;    
    return 1;
}

int main() {

    int i, j, k, flag, need_goods;
    while (scanf("%d%d%d", &shopkeeper_number, &place_number, &goods_number) != EOF) {
        if (!shopkeeper_number && !place_number && !goods_number) {
            break;
        }
        memset(head, -1, sizeof(head));
        edge_number = 0;
        flag = 1;
        costs = 0;
        for (i = 1; i <= shopkeeper_number; i++) {
            for (j = 1; j <= goods_number; j++) {
                scanf("%d", &orders[i][j]);
            }
        }
        for (i = 1; i <= place_number; i++) {
            for (j = 1; j <= goods_number; j++) {
                scanf("%d", &stored[i][j]);
            }
        }
        for (i = 1; i <= goods_number; i++) {
            for (j = 1; j <= shopkeeper_number; j++) {
                for (k = 1; k <= place_number; k++) {
                    scanf("%d", &goods_cost[i][j][k]);
                }
            }
        }
        source = 0;
        destination = place_number + shopkeeper_number + 1;
        for (i = 1; i <= goods_number && flag; i++) {
            memset(head, -1, sizeof(head));
            edge_number = 0;
            need_goods = 0;
            for (j = 1; j <= shopkeeper_number; j++) {
                need_goods += orders[j][i];
            }
            for (j = 1; j <= place_number; j++) {
                addEdge(source, j, stored[j][i], 0, 0, 0);
            }
            for (j = 1; j <= place_number; j++) {
                for (k = 1; k <= shopkeeper_number; k++) {
                    addEdge(j, k + place_number, orders[k][i], 0, goods_cost[i][k][j], -goods_cost[i][k][j]);
                }
            }
            for (j = 1; j <= shopkeeper_number; j++) {
                addEdge(j + place_number, destination, orders[j][i], 0, 0, 0);
            }
            flow = 0;
            while (spfa()) {
                ;
            }
            if (flow != need_goods) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            printf("%d\n", costs);
        }
        else {
            printf("-1\n");
        }
    }
    return 0;
}
