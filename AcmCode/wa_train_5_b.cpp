#include <string.h>
#include <cstdio>
#include <vector>
#include <iostream>


const int MAX_POINT = 1000005;
const int MAX_EDGE = 2000000;
const long long INF = 20000 * 100000;
struct Edge {
    int end;
    int value;
    int next;
};

struct Edge edge[MAX_EDGE];
int queue[MAX_POINT], cost[MAX_POINT], in[MAX_POINT], out[MAX_POINT], head[MAX_POINT], vis[MAX_POINT];
long long distance[MAX_POINT];
int source, destination, point_number, edge_number, add_number;
long long ans;


void addEdge(int start, int end, int value) {
    edge[add_number].end = end;
    edge[add_number].value = value;
    edge[add_number].next = head[start];
    head[start] = add_number;
    add_number++;
}
void spfa() {
    ans = -INF;
    for (int i = 0; i <= point_number + 1; i++) {
        distance[i] = -INF;
    }
    int front = 0;
    int rear = 1;
    distance[source] = 0;
    queue[front] = source;
    while (front < rear) {
        int cnt_point = queue[front];
        vis[cnt_point] = 1;
        for (int next_edge = head[cnt_point]; next_edge != -1; next_edge = edge[next_edge].next) {
            int next_point = edge[next_edge].end;
            if (distance[next_point] < distance[cnt_point] + edge[next_edge].value) {
                distance[next_point] = distance[cnt_point] + edge[next_edge].value;
                if (!vis[next_point]) {
                    queue[rear] = next_point;
                    vis[next_point] = 1;
                    rear++;
                }
            }
        }
        vis[cnt_point] = 0;
        front++;
    }
}

int main() {

    while (scanf("%d%d", &point_number, &edge_number) != EOF) {
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        memset(head, -1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        add_number = 0;
        for (int i = 1; i <= point_number; i++) {
            scanf("%d", &cost[i]);
        }
        source = 0;
        destination = point_number + 1;
        for (int i = 1; i <= edge_number; i++) {
            int start, end;
            scanf("%d%d", &start, &end);
            addEdge(start, end, cost[end]);
        }
        for (int i = 1; i <= point_number; i++) {
            if (in[i] == 0) {
                addEdge(source, i, cost[i]);
            }
        }
        spfa();
        long long max_number = -INF;
        for (int i = 1; i <= point_number; i++) {
            if (out[i] == 0) {
                if (distance[i] > max_number) {
                    max_number = distance[i];
                }
            }
        }
        std::cout << max_number << std::endl;
    }
    return 0;
}
