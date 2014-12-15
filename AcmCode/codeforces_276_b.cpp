#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn = 200009;
using namespace std;

int n, val[maxn], vis[maxn * 10];
int main() {
//    freopen("in.txt", "r", stdin);
    memset(vis, 0, sizeof(vis));
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        vis[val[i]] = val[i];
    }
    sort(val + 1, val + 1 + n);
    int m = unique(val + 1, val + 1 + n) - val - 1;
    for (int i = 1; i <= val[m] * 2; i++) {
        if (!vis[i]) {
            vis[i] = vis[i - 1];
        }
    }
    int max_ans = 0;
    for (int i = 1; i < m; i++) {
        for (int j = 2; j * val[i] <= 2 * val[m]; j++) {
            int cnt = j * val[i];
            cnt = vis[cnt - 1];
            max_ans = max(max_ans, cnt % val[i]);
        }
    }
    printf("%d\n", max_ans);
    return 0;
}

