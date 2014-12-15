#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 2007;
int n;
vector<int> path[maxn], ans;
int que[maxn * maxn], ok[maxn], vis[maxn];
void bfs(int cnt) {
    for (int i = 1; i <= n; i++) {
        vis[i] = 0;
    }
    int front = 0;
    int rear = 1;
    int num = 1;
    que[front] = cnt;
    vis[cnt] = 1;
    while (front < rear) {
        int x = que[front];
        if (num == n) {
            break;
        }
        for (int i = 0; i < path[x].size(); i++) {
            int v = path[x][i];
            if (ok[v]) {
                num = n;
                break;
            }
            if (!vis[v]) {
                vis[v] = 1;
                num++;
                que[rear++] = v;
            }
        }
        front++;
    }
    if (num == n) {
        ok[cnt] = 1;
        ans.push_back(cnt);
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    memset(ok, 0, sizeof(ok));
    for (int i = 1; i <= n; i++) {
        while (1) {
            int a;
            scanf("%d", &a);
            if (!a) {
                break;
            }
            path[i].push_back(a);
        }
    }
    for (int i = 1; i <= n; i++) {
        bfs(i);
    }
    ans.push_back(0);
    for (int i = 0; i < ans.size(); i++) {
        if (i) {
            printf(" ");
        }
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
