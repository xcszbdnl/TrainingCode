#include <stdio.h>
#include <string.h>

#define MAX_EDGE 1000000
#define MAX_POINT 20005
#define INF 1000000

struct Edge {
    int start;
    int end;
    int cap;
    int next;
};

struct Edge edge[MAX_EDGE];
int head[MAX_POINT], cur[MAX_POINT], cur[MAX_POINT], distance[MAX_POINT], queue[MAX_POINT * 4], stack[MAX_POINT];
int source, destination, module_number, pair_number, edge_number;

int bfs() {
    int front, rear, i, cnt_point, previous_point, end;
    front = 0;
    rear = 1;
    queue[front] = source;
    memset(distance, -1, sizeof(distance));
    distance[source] = 0;
    while (front < rear) {
        cnt_point = queue[front];
        for (i = head[cnt_point]; i != -1; i = edge[i].next) {
            end = edge[i].end;
            if (edge[i].cap > 0 && distance[end] == -1) {
                distance[end] = distance[cnt_point] + 1;
                queue[rear++] = end;
                if (end == destination) {
                    return 1;
                }
            }
        }
        front++;
    }
    return 0;
}

void addEdge(int start, int end, int value_1, int value_2) {
    edge[edge_number].start = start;
    edge[edge_number].end = end;
    edge[edge_number].cap = value_1;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;

    edge[edge_number].start = end;
    edge[edge_number].end = start;
    edge[edge_number].cap = value_2;
    edge[edge_number].next = head[end];
    head[end] = edge_number;
    edge_number++;
}

int dinic() {
    int flow = 0;
    int i, top, cnt_point, min_flow, location;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        top = 0;
        cnt_point = source;
        while (1) {
            if (cnt_point == destination) {
                min_flow = INF;
                for (i = 0; i < top; i++) {
                    if (min_flow > edge[stack[i]].cap) {
                        min_flow = edge[stack[i]].cap;
                        location = i;
                    }
                }
                for (i = 0; i < top; i++) {
                    edge[stack[i]].cap -= min_flow;
                    edge[stack[i] ^ 1].cap += min_flow;
                }
                flow += min_flow;
                top = location;
                cnt_point = edge[stack[top]].start;
            }
            for (i = cur[cnt_point]; i != -1; cur[cnt_point] = i = edge[i].next) {
                if (edge[i].cap != 0 && distance[edge[i].end] == distance[cnt_point] + 1) {
                    break;
                }
            }
            if (cur[cnt_point] != -1) {
                stack[top] = cur[cnt_point];
                top++;
                cnt_point = edge[cur[cnt_point]].end;
            }
            else {
                if (top == 0) {
                    break;
                }
                distance[cnt_point] = -1;
                top--;
                cnt_point = edge[stack[top]].start;
            }
        }
    }
    return flow;
}

int main() {

    int i, core_1, core_2, pair_1, pair_2, cost, value;
    while (scanf("%d%d", &module_number, &pair_number) != EOF) {
        edge_number = 0;
        source = 0;
        destination = module_number + 1;
        memset(head, -1, sizeof(head));
        for (i = 1; i <= module_number; i++) {
            scanf("%d%d", &core_1, &core_2);
            addEdge(source, i, core_1, 0);
            addEdge(i, destination, core_2, 0);
        }
        for (i = 0; i < pair_number; i++) {
            scanf("%d%d%d", &pair_1, &pair_2, &cost);
            addEdge(pair_1, pair_2, cost, cost);
        }
        value = dinic();
        printf("%d\n", value);
    }
    return 0;
}
