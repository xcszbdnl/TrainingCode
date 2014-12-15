#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 111111

struct Edge {
    int end;
    int next;
};

struct Edge edge[MAX_NUMBER];
int father[MAX_NUMBER], vis[MAX_NUMBER], head[MAX_NUMBER];
int point_number, edge_number, ans, search_1, search_2;

void addEdge(int start, int end) {
    edge[edge_number].end = end;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;
}

int find(int u) {
    if (u == father[u]) {
        return u;
    }
    father[u] = find(father[u]);
    return father[u];

}

void tarjan(int u) {
    int next_edge, end;
    father[u] = u;
    for (next_edge = head[u]; next_edge != 0; next_edge = edge[next_edge].next) {
        end = edge[next_edge].end;
        tarjan(end);
        father[end] = u;
    }
    if (u == search_1 && father[search_2]) {
        ans = find(search_2);
    }
    else if (u == search_2 && father[search_1]) {
        ans = find(search_1);
    }
}

int main() {

    int test_case, i, start, end;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(head, 0, sizeof(head));
        memset(vis, 0, sizeof(vis));
        memset(father, 0, sizeof(father));
        scanf("%d", &point_number);
        edge_number = 1;
        for (i = 1; i < point_number; i++) {
            scanf("%d%d", &start, &end);
            addEdge(start, end);
            vis[end] = start;
        }
        scanf("%d%d", &search_1, &search_2);
        for (i = 1; i <= point_number; i++) {
            if (!vis[i]) {
                tarjan(i);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
