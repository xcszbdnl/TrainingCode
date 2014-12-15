#include <stdio.h>
#include <string.h>

#define MAX_EDGE 50000
#define MAX_POINT 45000
#define MAX_QUERY 10005

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

struct Edge edge[MAX_EDGE];
struct Query query[MAX_QUERY];
int rank[MAX_POINT], father[MAX_POINT], ancestor[MAX_POINT], distance[MAX_POINT], query_head[MAX_POINT], head[MAX_POINT];
int vis[MAX_POINT], ans[MAX_POINT];
int point_number, edge_number, query_number;

void addEdge(int start, int end, int value) {
    edge[edge_number].end = end;
    edge[edge_number].value = value;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;
}

void addQuery(int point_1, int point_2, int order) {
    query[query_number].end = point_2;
    query[query_number].order = order;
    query[query_number].next = query_head[point_1];
    query_head[point_1] = query_number;
    query_number++;

    query[query_number].end = point_1;
    query[query_number].order = order;
    query[query_number].next = query_head[point_2];
    query_head[point_2] = query_number;
    query_number++;
}

void makeSet(int cnt_point) {
    father[cnt_point] = cnt_point;
    rank[cnt_point] = 0;
}

int find(int cnt_point) {
    int root;
    if (cnt_point == father[cnt_point]) {
        return cnt_point;
    }
    else {
        root = find(father[cnt_point]);
        father[cnt_point] = root;
        return father[cnt_point];
    }
}

void setUion(int x, int y) {
    if (rank[x] > rank[y]) {
        father[y] = x;
    }
    else {
        father[x] = y;
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }
}

void tarjan(int cnt_point) {
    int end, next_edge, next_query;
    makeSet(cnt_point);
    ancestor[cnt_point] = cnt_point;
    vis[cnt_point] = 1;
    for (next_edge = head[cnt_point]; next_edge != 0; next_edge = edge[next_edge].next) {
        end = edge[next_edge].end;
        if (!vis[end]) {
            distance[end] = distance[cnt_point] + edge[next_edge].value;
            tarjan(end);
            setUion(cnt_point, end);
            ancestor[find(end)] = cnt_point;
        }
    }
    for (next_query = query_head[cnt_point]; next_query != 0; next_query = query[next_query].next) {
        end = query[next_query].end;
        if (vis[end]) {
            ans[query[next_query].order] = distance[cnt_point] + distance[end] - 2 * distance[ancestor[find(end)]];
        }
    }
}

void init() {
    edge_number = 1;
    query_number = 1;
    memset(distance, 0, sizeof(distance));
    memset(head, 0, sizeof(head));
    memset(query_head, 0, sizeof(head));
    memset(ans, 0, sizeof(ans));
    memset(rank, 0, sizeof(rank));
    memset(father, 0, sizeof(father));
    memset(vis, 0, sizeof(vis));
    memset(ancestor, 0, sizeof(ancestor));
}

int main() {

    int i, j, start, end, value, edges, number, point_1, point_2;
    char direction[10];
    while (scanf("%d%d", &point_number, &edges) != EOF) {
        init();
        for (i = 1; i <= edges; i++) {
            scanf("%d%d%d%s", &start, &end, &value, direction);
            addEdge(start, end, value);
            addEdge(end, start, value);
        }
        scanf("%d", &number);
        for (i = 1; i <= number; i++) {
            scanf("%d%d", &point_1, &point_2);
            addQuery(point_1, point_2, i);
        }
        distance[1] = 0;
        tarjan(1);
        for (i = 1; i <= number; i++) {
            printf("%d\n", ans[i]);
        }
    }
}
