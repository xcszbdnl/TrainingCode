#include <cstdio>
#include <cstring>

const int maxn = 40007;

int fa[maxn];
int x[maxn], y[maxn];
int n, m;

struct Edge {
    int u, v, len;
    char op;
};

struct Edge edge[maxn];

int abs(int num) {
    return num < 0 ? -num : num;
}
int findFa(int cnt) {
    if (cnt == fa[cnt]) {
        return cnt;
    }
    int tmp = fa[cnt];
    fa[cnt] = findFa(fa[cnt]);
    x[cnt] += x[tmp];
    y[cnt] += y[tmp];
    return fa[cnt];
}
void addEdge(int cnt) {
    int a = findFa(edge[cnt].u);
    int b = findFa(edge[cnt].v);
    fa[b] = a;
    x[b] = x[edge[cnt].u] - x[edge[cnt].v];
    y[b] = y[edge[cnt].u] - y[edge[cnt].v];
    switch(edge[cnt].op) {
    case 'N':
        y[b] += edge[cnt].len;
        break;
    case 'S':
        y[b] -= edge[cnt].len;
        break;
    case 'E':
        x[b] += edge[cnt].len;
        break;
    case 'W':
        x[b] -= edge[cnt].len;
        break;
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= m; i++) {
            char temp[10];
            scanf("%d%d%d%s", &edge[i].u, &edge[i].v, &edge[i].len, temp);
            edge[i].op = temp[0];
        }
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
        int cnt_edge = 1;
        int q;
        scanf("%d", &q);
        for (int i = 1; i <= q; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            for (; cnt_edge <= c; cnt_edge++) {
                addEdge(cnt_edge);
            }
            int cnt_x = findFa(a);
            int cnt_y = findFa(b);
            if (cnt_x != cnt_y) {
                printf("-1\n");
            }
            else {
                int ans = abs(x[a] - x[b]);
                ans += abs(y[a] - y[b]);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
