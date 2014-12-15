#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_NUMBER = 100007;

struct Edge {
    int start, end, next;
};
struct Edge edge[MAX_NUMBER * 2];
int head[MAX_NUMBER], edge_number;
int high[MAX_NUMBER], low[MAX_NUMBER], vis[MAX_NUMBER], arr[MAX_NUMBER], picked[MAX_NUMBER];
int n, depth;
int lowbit(int x) {
    return x & -x;
}

int sum(int x) {
    int ans = 0;
    while (x > 0) {
        ans += arr[x];
        x -= lowbit(x);
    }
    return ans;
}
void add(int x, int d) {
    while (x <= n) {
        arr[x] += d;
        x += lowbit(x);
    }
}

void addEdge(int start, int end) {
    edge[edge_number].start = start;
    edge[edge_number].end = end;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;

    edge[edge_number].start = end;
    edge[edge_number].end = start;
    edge[edge_number].next = head[end];
    head[end] = edge_number;
    edge_number++;
}

void dfs(int cnt_point) {
    low[cnt_point] = ++depth;
    for (int i = head[cnt_point]; i != -1; i = edge[i].next) {
        int next_point = edge[i].end;
        if (!vis[next_point]) {
            vis[next_point] = 1;
            dfs(next_point);
        }
    }
    high[cnt_point] = depth;
}
int main() {

    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int start, end;
        scanf("%d%d", &start, &end);
        addEdge(start, end);
    }
    for (int i = 1; i <= n; i++) {
        add(i, 1);
    }
    depth = 0;
    vis[1] = 1;
    dfs(1);
    int m;
    scanf("%d", &m);
    while (m--) {
        char operation[10];
        scanf("%s", operation);
        if (operation[0] == 'Q') {
            int order;
            scanf("%d", &order);
            int sums_1 = sum(low[order] - 1);
            int sums_2 = sum(high[order]);
            printf("%d\n", sums_2 - sums_1);
        }
        else {
            int order;
            scanf("%d", &order);
            if (picked[order]) {
                add(low[order], 1);
                picked[order] = 0;
            }
            else {
                add(low[order], -1);
                picked[order] = 1;
            }
        }
    }
    return 0;
}
