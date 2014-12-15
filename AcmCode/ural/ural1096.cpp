#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
const int maxn = 1007;
struct P {
    int up, down;
    int d, fa, order;
};

vector<int> path[maxn];
struct P que[maxn];
struct P p[maxn];
int vis[maxn];
int dest, n, flag, start_x, start_y;

void addEdge() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[i].up == p[j].up || p[i].down == p[j].up) {
//                printf("%d--->%d\n", i, j);
                path[i].push_back(j);
            }
        }
    }
}

int bfs() {
    memset(vis, 0, sizeof(vis));
    vis[n] = 1;
    que[0] = p[n];
    int front = 0;
    int rear = 1;
    while (front < rear) {
        struct P cnt = que[front];
        if (p[cnt.order].down == dest || p[cnt.order].up == dest) {
            return front;
        }
        for (int i = 0; i < path[cnt.order].size(); i++) {
            int v = path[cnt.order][i];
            if (!vis[v]) {
                vis[v] = 1;
                struct P next;
                next.fa = front;
                next.d = cnt.d + 1;
                next.order = v;
                que[rear++] = next;
            }
        }
        front++;
    }
    return -1;
}
void printAns(struct P cnt) {
    if (cnt.fa == -1) {
        return;
    }
    printAns(que[cnt.fa]);
    printf("%d\n", cnt.order);
}
int main() {
//    freopen("in.txt", "r", stdin);
    flag = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].up, &p[i].down);
        p[i].order = i;
    }
    scanf("%d%d%d", &dest, &start_x, &start_y);
    n++;
    p[n].order = n;
    p[n].fa = -1;
    p[n].d = 0;
    p[n].up = start_x;
    p[n].down = start_y;
    addEdge();
    flag = bfs();
    if (flag == -1) {
        printf("IMPOSSIBLE\n");
    }
    else {
        printf("%d\n", que[flag].d);
        printAns(que[flag]);
    }
    return 0;
}
