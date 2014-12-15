#include <string.h>
#include <cstdio>

const int MAX_POINT = 50006;
const int MAX_EDGE = MAX_POINT * 4;
const int INF = 999999999;

#define max(a,b) ((a) > (b)) ? (a) : (b)

struct Edge {
    int end;
    int value;
    int next;
};

struct Edge edge[MAX_EDGE];
int distance[MAX_POINT], vis[MAX_POINT], queue[MAX_POINT * 10], head[MAX_POINT];
int point_number, edge_number, interval_number, max_point;

void addEdge(int start, int end, int value) {
    edge[edge_number].end = end;
    edge[edge_number].value = value;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;
}

void spfa() {
    for (int i = 0; i <= max_point; i++) {
        distance[i] = -INF;
    }
    distance[0] = 0;
    int front, rear;
    front = 0;
    rear = 1;
    queue[front] = 0;
    while (front < rear) {
        int cnt_point = queue[front];
        vis[cnt_point] = 1;
        for (int next_edge = head[cnt_point]; next_edge != -1; next_edge = edge[next_edge].next) {
            int end = edge[next_edge].end;
            if (distance[end] < distance[cnt_point] + edge[next_edge].value) {
                distance[end] = distance[cnt_point] + edge[next_edge].value;
                if (!vis[end]) {
                    vis[end] = 1;
                    queue[rear] = end;
                    rear++;
                }
            }
        }
        vis[cnt_point] = 0;
        front++;
    }
}

int main() {

    scanf("%d", &interval_number);
    max_point = edge_number = 0;
    memset(vis, 0, sizeof(vis));
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= interval_number; i++) {
        int start, end, value;
        scanf("%d%d%d", &start, &end, &value);
        end++;
        addEdge(start, end, value);
        max_point = max(max_point, end);
    }
    for (int i = 0; i < max_point; i++) {
        addEdge(i, i + 1, 0);
        addEdge(i + 1, i, -1);
    }
    spfa();
    printf("%d\n", distance[max_point]);
    return 0;
}
