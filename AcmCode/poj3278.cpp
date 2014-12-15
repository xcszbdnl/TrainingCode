#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_NUMBER = 200007;
int n, k, que[MAX_NUMBER], dist[MAX_NUMBER], vis[MAX_NUMBER];
vector<int> path[MAX_NUMBER];

void spfa() {
    for (int i = 0; i < MAX_NUMBER; i++) {
        dist[i] = MAX_NUMBER * 10;
    }
    dist[n] = 0;
    int front = 0;
    int rear = 1;
    que[front] = n;
    memset(vis, 0, sizeof(vis));
    while (front < rear) {
        int cnt = que[front];
        vis[front] = 1;
        for (int i = 0; i < path[cnt].size(); i++) {
            int next_point = path[cnt][i];
            if (dist[next_point] > dist[cnt] + 1) {
                dist[next_point] = dist[cnt] + 1;
                if (!vis[next_point]) {
                    vis[next_point] = 1;
                    que[rear++] = next_point;
                    rear %= MAX_NUMBER;
                }
            }
        }
        vis[front] = 0;
        front++;
        front %= MAX_NUMBER;
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    for (int i = 0; i < MAX_NUMBER; i++) {
        int end = i - 1;
        if (end >= 0) {
            path[i].push_back(end);
        }
        end = i + 1;
        if (end < MAX_NUMBER) {
            path[i].push_back(end);
        }
        end = i * 2;
        if (end < MAX_NUMBER) {
            path[i].push_back(end);
        }
    }
//    while (scanf("%d%d", &n, &k) != EOF) {
    scanf("%d%d", &n, &k);
        if (n > k) {
            int temp = n;
            n = k;
            k = temp;
        }
        spfa();
        printf("%d\n", dist[k]);
    return 0;
}
