#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 500;
const int INF = 100000007;
struct Person {
    int money, start, type;
};
struct Tram {
    int k, route[maxn];
};
vector<int> path[maxn];
struct Tram tram[maxn];
struct Person person[maxn];
int n, m, k, dist[maxn], destination, vis[maxn], que[maxn];

void spfa(int start) {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= n + m + k; i++) {
        dist[i] = INF;
    }
    int front, rear;
    front = 0;
    rear = 1;
    que[front] = start;
    vis[start] = 1;
    dist[start] = 0;
    while (front < rear) {
        int cnt = que[front];
        for (int i = 0; i < path[cnt].size(); i++) {
            int next = path[cnt][i];
            if (dist[next] > dist[cnt] + 1) {
                dist[next] = dist[cnt] + 1;
                if (!vis[next]) {
                    vis[next] = 1;
                    que[rear++] = next;
                }
            }
        }
        vis[cnt] = 0;
        front++;
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &tram[i].k);
        for (int j = 1; j <= tram[i].k; j++) {
            scanf("%d", &tram[i].route[j]);
        }
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d%d%d", &person[i].money, &person[i].start, &person[i].type);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            int flag = 0;
            for (int p = 1; p <= tram[i].k && !flag; p++) {
                for (int q = 1; q <= tram[j].k && !flag; q++) {
                    if (tram[i].route[p] == tram[j].route[q]) {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag) {
//                printf("%d:%d\n",i, j);
                path[i].push_back(j);
                path[j].push_back(i);
            }
        }
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= m; j++) {
            int flag = 0;
            for (int p = 1; p <= tram[j].k; p++) {
                if (person[i].start == tram[j].route[p]) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
//                printf("%d:%d\n", i + m, j);
                path[i + m].push_back(j);
            }
        }
    }
    int ans = -1;
    int min_cost = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int flag = 0;
            for (int p = 1; p <= tram[j].k; p++) {
                if (tram[j].route[p] == i) {
//                    printf("%d:%d\n", j, m + k + i);
                    path[j].push_back(m + k + i);
                    break;
                }
            }
        }
        int temp = 0;
        int flag = 0;
        destination = m + k + i;
        for (int j = 1; j <= k; j++) {
            spfa(j + m);
            if (person[j].start != i && dist[destination] >= INF) {
                flag = 1;
                break;
            }
            dist[destination]--;
            if (person[j].type != 1 && person[j].money < dist[destination] * 4) {
                flag = 1;
                break;
            }
            if (person[j].type == 0 && person[j].start != i) {
                temp += dist[destination] * 4;
            }
        }
        if (!flag && min_cost > temp) {
            ans = i;
            min_cost = temp;
        }
    }
    if (min_cost < INF) {
        printf("%d %d\n", ans, min_cost);
    }
    else {
        printf("0\n");
    }
    return 0;
}
