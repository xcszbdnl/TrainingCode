#include <string.h>
#include <cstdio>
#include <iostream>

const int MAX_POINT = 100005;
const int MAX_EDGE = 1000006;
const long long INF = 20000 * 100000;

struct Edge {
    int end;
    int next;
};

struct Edge edge[MAX_EDGE];
int vis[MAX_POINT], in[MAX_POINT], out[MAX_POINT], head[MAX_POINT], cost[MAX_POINT];
long long dp[MAX_POINT];
int ans, point_number, edge_number, add_number;

void addEdge(int start, int end) {
    edge[add_number].end = end;
    edge[add_number].next = head[start];
    head[start] = add_number;
    add_number++;
}

int main() {

    while (scanf("%d%d", &point_number, &edge_number) != EOF) {
        memset(vis, 0, sizeof(vis));
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        memset(head, -1, sizeof(head));
        add_number = 0;
        for (int i = 1; i <= point_number; i++) {
            scanf("%d", &cost[i]);
        }
        for (int i = 1; i <= edge_number; i++) {
            int start;
            int end;
            scanf("%d%d", &start, &end);
            in[end]++;
            out[start]++;
            addEdge(start, end);
        }
        int ans = -INF;
        for (int i = 1; i  <= point_number; i++) {
            if (in[i] == 0) {
                dp[i] = cost[i];
            }
            else {
                dp[i] = -INF;
            }
        }
        int cnt_number = 1;
        while (cnt_number < point_number) {
            for (int i = 1; i <= point_number; i++) {
                if (in[i] == 0 && !vis[i]) {
                    vis[i] = 1;
                    cnt_number++;
                    for (int next_edge = head[i]; next_edge != -1; next_edge = edge[next_edge].next) {
                        int next_point = edge[next_edge].end;
                        in[next_point]--;
                        if (dp[next_point] < dp[i] + cost[next_point]) {
                            dp[next_point] = dp[i] + cost[next_point];
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= point_number; i++) {
            if (out[i] == 0) {
                if (ans < dp[i]) {
                    ans = dp[i];
                }
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
