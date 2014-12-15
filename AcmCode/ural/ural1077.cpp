#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 207;
const int INF = 10000007;
int  n, m, ans_num, fa[maxn];
int que[maxn * maxn], que_fa[maxn * maxn], vis[maxn];
vector<int> ans[maxn * maxn];
vector<int> path[maxn];

int findFa(int x) {
    return x == fa[x] ? x : fa[x] = findFa(fa[x]);
}

void bfs(int source, int dest) {
    memset(vis, 0, sizeof(vis));
    que_fa[0] = -1;
    que[0] = source;
    vis[source] = 1;
    int front, rear;
    front = 0;
    rear = 1;
    while (front < rear) {
        int cnt = que[front];
        if (cnt == dest) {
            ans[ans_num].clear();
            cnt = front;
            while (cnt != -1) {
                ans[ans_num].push_back(que[cnt]);
                cnt = que_fa[cnt];
            }
            ans_num++;
            return ;
        }
        for (int i = 0; i < path[cnt].size(); i++) {
            int v = path[cnt][i];
            if (!vis[v]) {
                vis[v] = 1;
                que[rear] = v;
                que_fa[rear++] = front;
            }
        }
        front++;
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    ans_num = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        int x, y;
        x = findFa(a);
        y = findFa(b);
        if (x == y) {
            bfs(b, a);
        }
        else {
            fa[x] = y;
            path[a].push_back(b);
            path[b].push_back(a);
        }
    }
    printf("%d\n", ans_num);
    for (int i = 0; i < ans_num; i++) {
        printf("%d", ans[i].size());
        for (int j = 0; j < ans[i].size(); j++) {
            printf(" %d", ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
