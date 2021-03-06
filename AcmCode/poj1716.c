#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 100006
#define INF 100000000
#define max(a,b) ((a) > (b)) ? (a) : (b)

struct Edge {
    int end;
    int value;
    int next;
};

struct Edge edge[MAX_NUMBER * 4];
int queue[MAX_NUMBER * 10];
int head[MAX_NUMBER];
int vis[MAX_NUMBER], distance[MAX_NUMBER];
int max_number, edge_number;

void addEdge(int start, int end, int value) {
    edge[edge_number].end = end;
    edge[edge_number].value = value;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;
}

void spfa() {
    int i, front, rear, cnt_node, next_node, next_edge;
    for (i = 0; i <= max_number; i++) {
        distance[i] = -INF;
    }
    front = 0;
    rear = 1;
    queue[front] = 0;
    distance[0] = 0;
    while (front < rear) {
        cnt_node = queue[front];
        vis[cnt_node] = 1;
        for (next_edge = head[cnt_node]; next_edge != 0; next_edge = edge[next_edge].next) {
            next_node = edge[next_edge].end;
            if (distance[next_node] < distance[cnt_node] + edge[next_edge].value) {
                distance[next_node] = distance[cnt_node] + edge[next_edge].value;
                if (!vis[next_node]) {
                    vis[next_node] = 1;
                    queue[rear] = next_node;
                    rear++;
                }
            }
        }
        vis[cnt_node] = 0;
        front++;
    }
}

int main() {

    int interval_number, i, start, end;
    while (scanf("%d", &interval_number) != EOF) {
        edge_number = 1;
        max_number = 0;
        memset(head, 0, sizeof(head));
        memset(edge, 0, sizeof(edge));
        for (i = 0; i < interval_number; i++) {
            scanf("%d%d", &start, &end);
            end++;
            max_number = max(max_number, end);
            addEdge(start, end, 2);
        }
        for (i = 0; i < max_number; i++) {
            addEdge(i, i + 1, 0);
            addEdge(i + 1, i, -1);
        }
        spfa();
        printf("%d\n", distance[max_number]);
    }
    return 0;
}
