#include <stdio.h>
#include <string.h>

#define MAX_POINT 100005


struct Edge {
    int end;
    int value;
    int next;
};


struct Query {
    int end;
    int order;
    int next;
};

struct Edge edge[MAX_POINT * 2];
struct Query query[MAX_POINT * 2];
int distance[MAX_POINT], father[MAX_POINT], vis[MAX_POINT], head[MAX_POINT], query_head[MAX_POINT], ans[MAX_POINT];
int point_number, edge_number, query_number;

void init() {
    edge_number = 1;
    query_number = 1;
    memset(distance, 0, sizeof(distance));
    memset(father, 0, sizeof(father));
    memset(head, 0, sizeof(head));
    memset(query_head, 0, sizeof(query_head));
    memset(vis, 0, sizeof(vis));
}


void addEdge(int start, int end, int value) {
    edge[edge_number].end = end;
    edge[edge_number].value = value;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;
}

void addQuery(int start, int end, int order) {
    query[query_number].end = end;
    query[query_number].order = order;
    query[query_number].next = query_head[start];
    query_head[start] = query_number;
    query_number++;
}

int find(int cnt_point) {
    if (cnt_point != father[cnt_point]) {
        father[cnt_point] = find(father[cnt_point]);
        return father[cnt_point];
    }
    else {
        return cnt_point;
    }
}

void tarjan(int cnt_point) {
    int next_edge, next_query, end;
    vis[cnt_point] = 1;
    father[cnt_point] = cnt_point;
    for (next_edge = head[cnt_point]; next_edge != 0; next_edge = edge[next_edge].next) {
        end = edge[next_edge].end;
        if (!vis[end]) {
            distance[end] = distance[cnt_point] + edge[next_edge].value;
            tarjan(end);
            father[end] = cnt_point;
        }
    }
    for (next_query = query_head[cnt_point]; next_query != 0; next_query = query[next_query].next) {
        end = query[next_query].end;
        if (vis[end]) {
            ans[query[next_query].order] = distance[cnt_point] + distance[end] - 2 * distance[find(father[end])];
        }
    }
}

int main() {

    int i, edges, start, end, value, number;
    char operation[10];
    while (scanf("%d%d", &point_number, &edges) != EOF) {
        init();
        for (i = 1; i <= edges; i++) {
            scanf("%d%d%d%s", &start, &end, &value, operation);
            addEdge(start, end, value);
            addEdge(end, start, value);
        }
        scanf("%d", &number);
        for (i = 1; i <= number; i++) {
            scanf("%d%d", &start, &end);
            addQuery(start, end, i);
            addQuery(end, start, i);
        }
        distance[1] = 0;
        tarjan(1);
        for (i = 1; i <= number; i++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}


    
    
