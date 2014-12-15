#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;
const int maxn = 19;
const int INF = 10000000;
int maps[maxn][maxn];
int n, m;
long long ans;
long long dp[(1 << maxn) + 2][maxn + 2];


int getFirst(int sta) {
    for (int i = 0; i < n; i++) {
        if (sta & (1 << i)) {
            return i;
        }
    }
}

int countBit(int sta) {
    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (sta & (1 << i)) {
            ret++;
        }
    }
    return ret;
}
int main() {
    freopen("in.txt", "r", stdin);
    memset(dp, 0, sizeof(dp));
    memset(maps, 0, sizeof(maps));
    scanf("%d%d", &n, &m);
    ans = 0;
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d",&a, &b);
        a--;
        b--;
        dp[(1 << a)][a] = 1;
        dp[(1 << b)][b] = 1;
        maps[a][b] = maps[b][a] = 1;
    }
    int tot = (1 << n);
    for (int i = 1; i < tot; i++) {
        int first = getFirst(i);
        for (int j = first + 1; j < n; j++) {
            if (i & (1 << j)) {
                for (int m = first; m < n; m++) {
                    if (i & (1 << m) && (m != j) && maps[m][j]) {
                        dp[i][j] += dp[i ^ (1 << j)][m];
                    }
                }
            }
            if (countBit(i) >= 3 && maps[first][j]) {
                ans += dp[i][j];
            }
        }
    }
    printf("%I64d\n", ans / 2);
    return 0;
}
