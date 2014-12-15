#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>

const int maxn = 100007;

using namespace std;
vector<int> path[maxn];
int n, m, ans, num[maxn];
int que[maxn];
void bfs(int cnt) {
    for (int i = 1; i <= n; i++) {
        num[i] = 0;
    }
    int front = 0;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        que[front++] = v;
    }
    for (int i = 0; i < front; i++) {
        for (int j = 0; j < path[que[i]].size(); j++) {
            int v = path[que[i]][j];
            if (v == cnt) {
                continue;
            }
            num[v]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i != cnt && num[i] >= 2) {
            ans = ans + num[i] * (num[i] - 1) / 2;
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(b);
    }
    ans = 0;
    for (int i = 1; i <= n; i++) {
        bfs(i);
    }
    printf("%d\n", ans);
    return 0;
}

/*
7 8
1 2
2 3
1 4
4 3
5 4
5 6
4 7
6 3

4 7
1 2
2 1
2 3
1 3
2 4
1 4
4 3

4 8
1 2
2 3
1 4
4 3
3 4
3 2
2 1
4 1
*/
