/**
 *To get the max flow in a graph
 *Use the adjcent table to express the graph
 */

struct Edge {
    int start;
    int end;
    int cap;
    int next;
};


struct Edge edge[MAX_EDGE];
int cur[MAX_POINT];
int queue[MAX_POINT * 4];
int distance[MAX_POINT];
int stack[MAX_POINT];
int head[MAX_POINT];


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
    int front, rear, cnt_point, i, end;
    front = 0;
    rear = 1;
    memset(distance, -1, sizeof(distance));
    queue[front] = source;
    distance[source] = 0;
    while (front < rear) {
        cnt_point = queue[front];
        for (i = head[cnt_point]; i != -1; i = edge[i].next) {
            end = edge[i].end;
            if (edge[i].cap > 0 && distance[end] == -1) {
                distance[end] = distance[cnt_point] + 1;
                queue[rear] = end;
                rear++;
                if (end == destination) {
                    return 1;
                }
            }
        }
        front++;
    }
    return 0;
}

int dinic() {
    int flow, i, top, source, min_flow, min_flow_number;
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
                        min_flow_number = i;
                    }
                }
                for (i = 0; i < top; i++) {
                    edge[stack[i]].cap -= min_flow;
                    edge[stack[i] ^ 1].cap += min_flow;
                }
                flow += min_flow;
                top = min_flow_number;
                cnt_point = edge[stack[top]].start;
            }
            for (i = cur[cnt_point]; i != -1; cur[cnt_point] = i = edge[i].next) {
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
