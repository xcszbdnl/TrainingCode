#include <stdio.h>
#include <string.h>


#define MAX_POINT 1000
#define MAX_QUERY 300000

struct Edge {
    int end;
    int next;
};

struct Query {
    int end;
    int next;
};


struct Edge edge[MAX_POINT * 10];
struct Query query[MAX_QUERY];
int head[MAX_POINT], root[MAX_POINT], rank[MAX_POINT], ans[MAX_POINT], ancestor[MAX_POINT], checked[MAX_POINT], query_head[MAX_POINT];
int father[MAX_POINT];
int point_number, edge_number, query_number;
char input[MAX_POINT];

void addEdge(int start, int end) {
    edge[edge_number].end = end;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;
}

void buildEdge() {
    int i, start, end;
    int number = 0;
    scanf("%d%s", &start, input);
    for (i = 0; input[i] != '('; i++) {
        ;
    }
    i++;
    while (input[i] != ')') {
        number = number * 10 + input[i] - '0';
        i++;
    }
    for (i = 0; i < number; i++) {
        scanf("%d", &end);
        addEdge(start, end);
        root[end] = 1;
    }
}

void makeSet(int node) {
    father[node] = node;
    rank[node] = 0;
}

int find(int x) {
    int k;
    if (x == father[x]) {
        return x;
    }
    else {
        k = find(father[x]);
        father[x] = k;
        return k;
    }
}

void Union(int x, int y) {
    if (rank[x] > rank[y]) {
        father[y] = x; 
    }
    else {
        father[x] = y;
        if (rank[x] == rank[y]) {
            rank[y] = rank[y] + 1;
        }
    }
}

void tarjan(int cnt_point) {
    int next_edge, end, i;
    makeSet(cnt_point);
    ancestor[find(cnt_point)] = cnt_point;
    for (next_edge = head[cnt_point]; next_edge != 0; next_edge = edge[next_edge].next) {
        end = edge[next_edge].end;
        tarjan(end);
        Union(end, cnt_point);
        ancestor[find(cnt_point)] = cnt_point;
    }
    checked[cnt_point] = 1;
    for (i = query_head[cnt_point]; i != 0; i = query[i].next) {
        end = query[i].end;
        if (checked[end]) {
            ans[ancestor[find(end)]]++;
        }
    }
}

void solve() {
    int i;
    for (i = 1; i <= point_number; i++) {
        if (!root[i]) {
            tarjan(i);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int i, point_1, point_2, temp_1, temp_2, number;
    char c;
    while (scanf("%d", &point_number) != EOF) {
        memset(head, 0, sizeof(head));
        memset(checked, 0, sizeof(checked));
        memset(ans, 0, sizeof(ans));
        memset(root, 0, sizeof(root));
        memset(query_head, 0, sizeof(query_head));
        memset(rank, 0, sizeof(rank));
        memset(father, 0, sizeof(father));
        edge_number = 1;
        query_number = 1;
        for (i = 1; i <= point_number; i++) {
            buildEdge();
        }
        scanf("%d", &number);
        for (i = 1; i <= number; i++) {
            while ((c = getchar()) == ' ' || c == '\n' || c == '\t') {
                ;
            }
            scanf("%d%d", &point_1, &point_2);
            query[query_number].end = point_2;
            query[query_number].next = query_head[point_1];
            query_head[point_1] = query_number;
            query_number++;
            query[query_number].end = point_1;
            query[query_number].next = query_head[point_2];
            query_head[point_2] = query_number;
            query_number++;
            getchar();
        }
        solve();
        for (i = 1; i <= point_number; i++) {
            if (ans[i] > 0) {
                printf("%d:%d\n", i, ans[i]);
            }
        }
    }
    return 0;
}


