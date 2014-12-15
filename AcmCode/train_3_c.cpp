#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1105;
const int MAX_EDGE = 10000;
const int INF = 10000000;

struct Edge {
    int start;
    int end;
    int cap;
    int next;
};
    
int previous[MAX_NUMBER], pig_number[MAX_NUMBER], buy[MAX_NUMBER];
struct Edge edge[MAX_EDGE];
int queue[MAX_NUMBER], distance[MAX_NUMBER], stack[MAX_NUMBER], cur[MAX_NUMBER], head[MAX_NUMBER];
int house, customer, edge_number, source, destination;

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

int bfs() {
    int front = 0;
    int rear = 1;
    queue[front] = source;
    memset(distance, -1, sizeof(distance));
    distance[source] = 0;
    while (front < rear) {
        int cnt_point = queue[front];
        for (int cnt_edge = head[cnt_point]; cnt_edge != -1; cnt_edge = edge[cnt_edge].next) {
            int next_point = edge[cnt_edge].end;
            if (edge[cnt_edge].cap > 0 && distance[next_point] == -1) {
                distance[next_point] = distance[cnt_point] + 1;
                queue[rear] = next_point;
                rear++;
                if (next_point == destination) {
                    return 1;
                }
            }
        }
        front++;
    }
    return 0;
}

int dinic() {
    int cnt_point, min_flow_number, flow;
    flow = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        cnt_point = source;
        int top = 0;
        while (1) {
            if (cnt_point == destination) {
                int min_flow = INF;
                for (int i = 0; i < top; i++) {
                    if (min_flow > edge[stack[i]].cap) {
                        min_flow = edge[stack[i]].cap;
                        min_flow_number = i;
                    }
                }
                for (int i = 0; i < top; i++) {
                    edge[stack[i]].cap -= min_flow;
                    edge[stack[i] ^ 1].cap += min_flow;
                }
                flow += min_flow;
                top = min_flow_number;
                cnt_point = edge[stack[top]].start;
            }
            for (int i = cur[cnt_point]; i != -1; cur[cnt_point] = i = edge[i].next) {
                if (edge[i].cap > 0 && distance[edge[i].end] == distance[cnt_point] + 1) {
                    break;
                }
            }
            if (cur[cnt_point] != -1) {
                stack[top++] = cur[cnt_point];
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

    scanf("%d%d", &house, &customer);
    for (int i = 1; i <= house; i++) {
        scanf("%d", &pig_number[i]);
    }
    edge_number = 0;
    memset(previous, -1, sizeof(previous));
    memset(head, -1, sizeof(head));
    for (int i = 1 + house; i <= house + customer; i++) {
        int keys;
        scanf("%d", &keys);
        for (int j = 1; j <= keys; j++) {
            int key_number;
            scanf("%d", &key_number);
            if (previous[key_number] == -1) {
                addEdge(key_number, i, pig_number[key_number], 0);
                previous[key_number] = i;
            }
            else {
                addEdge(previous[key_number], i, INF, 0);
            }
        }
        scanf("%d", &buy[i]);
    }
    source = 0;
    destination = house + customer + 1;
    for (int i = 1; i <= house; i++) {
        addEdge(source, i, pig_number[i], 0);
    }
    for (int i = 1 + house; i <= house + customer; i++) {
        addEdge(i, destination, buy[i], 0);
    }
    int ans = dinic();
    printf("%d\n", ans);
    return 0;
}
