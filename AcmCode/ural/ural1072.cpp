#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 100;
const int INF = 1000007;

struct Computer {
    int k;
    unsigned int andNumber[maxn];
};
int n, start, dest, pre[maxn], que[maxn * 10], vis[maxn], dist[maxn], first;
vector<int> path[maxn];
struct Computer computer[maxn];

unsigned int convertToNumber(char *s) {
    unsigned int ret = 0;
    unsigned int cnt_number = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '.') {
            ret = ret * (1 << 8) + cnt_number;
            cnt_number = 0;
        }
        else {
            cnt_number = cnt_number * 10 + s[i] - '0';
        }
    }
    ret = ret * (1 << 8) + cnt_number;
    return ret;
}

void printAns(int cnt_node) {
    if (cnt_node != -1) {
        printAns(pre[cnt_node]);
        if (first) {
            printf("%d", cnt_node);
            first = 0;
        }
        else {
            printf(" %d", cnt_node);
        }
    }
}

void spfa() {
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    for (int i = 0; i <= n; i++) {
        dist[i] = INF;
    }
    int front = 0;
    int rear = 1;
    dist[start] = 0;
    vis[front] = 1;
    que[front] = start;
    while (front < rear) {
        int cnt_node = que[front];
        for (int i = 0; i < path[cnt_node].size(); i++) {
            int next = path[cnt_node][i];
            if (dist[next] > dist[cnt_node] + 1) {
                dist[next] = dist[cnt_node] + 1;
                pre[next] = cnt_node;
                if (!vis[next]) {
                    vis[next] = 1;
                    que[rear++] = next;
                }
            }
        }
        front++;
        vis[cnt_node] = 1;
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) {
            int k;
            scanf("%d", &k);
            computer[i].k = k;
            for (int j = 1; j <= k; j++) {
                char temp[100];
                scanf("%s", temp);
                unsigned int ip = convertToNumber(temp);
                scanf("%s", temp);
                unsigned int sub = convertToNumber(temp);
//                printf("sub:%u\n", sub);
                computer[i].andNumber[j] = ip & sub;
//                printf("and:%u\n", computer[i].andNumber[j]);
            }
        }
        scanf("%d%d", &start, &dest);
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int flag = 0;
                for (int k = 1; k <= computer[i].k && !flag; k++) {
                    for (int s = 1; s <= computer[j].k && !flag; s++) {
                        if (computer[i].andNumber[k] == computer[j].andNumber[s]) {
                            flag = 1;
                        }
                    }
                }
                if (flag) {
                    path[i].push_back(j);
                    path[j].push_back(i);
                }
            }
        }
        spfa();
        if (dist[dest] == INF) {
            printf("No\n");
        }
        else {
            printf("Yes\n");
            first = 1;
            printAns(dest);
            printf("\n");
        }
    }
}
