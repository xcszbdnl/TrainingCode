#include <cstdio>
#include <string.h>

const int MAX_POINT = 505;
const int MAX_EDGE = MAX_POINT * 2;

struct Edge {
    int end;
    int next;
};

struct Edge edge[MAX_EDGE];
int head[MAX_POINT], in[MAX_POINT], temp[MAX_POINT], vis[MAX_POINT];
int point_number, edge_number, add_number;

void addEdge(int start, int end) {
    edge[add_number].end = end;
    edge[add_number].next = head[start];
    head[start] = add_number;
    add_number++;
}

int test(int cnt_point) {
    int cnt_number = 1;
    memcpy(temp, in, sizeof(temp));
    memset(vis, 0, sizeof(vis));
    vis[cnt_point] = 1;
    for (int next_edge = head[cnt_point]; next_edge != -1; next_edge = edge[next_edge].next) {
        int end = edge[next_edge].end;
        temp[end]--;
    }
    while (cnt_number < point_number) {
        int first = -1;
        int next_point;
        for (int i = 0; i < point_number; i++) {
            if (temp[i] == 0 && !vis[i]) {
                if (first == -1) {
                    next_point = i;
                    first = 1;
                }
                else {
                    first = 2;
                }
            }
        }
        if (first == 2 || first == -1) {
            return 0;
        }
        vis[next_point] = 1;
        for (int next_edge = head[next_point]; next_edge != -1; next_edge = edge[next_edge].next) {
            int end = edge[next_edge].end;
            temp[end]--;
        }
        cnt_number++;
    }
    return 1;
}

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(head, -1, sizeof(head));
        memset(in, 0, sizeof(in));
        add_number = 0;
        scanf("%d%d", &point_number, &edge_number);
        int flag = 0;
        for (int i = 1; i <= edge_number; i++) {
            int start, end;
            scanf("%d%d", &start, &end);
            in[end]++;
            addEdge(start, end);
        }
        for (int i = 0; i < point_number; i++) {
            if (in[i] == 1) {
                if (test(i)) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            printf("Yeah, I'm superman\n");
        }
        else {
            printf("Your DAGy was initially defected!\n");
        }
    }
    return 0;
}
        
