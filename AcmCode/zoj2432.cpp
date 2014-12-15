#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


const int maxn = 507;
const int INF = 10000007;
using namespace std;
int next1[maxn], next2[maxn];
int a1[maxn], a2[maxn];
int n, m;
int dp[maxn][maxn];
int pre[maxn][maxn];

void printAns(int x, int loc) {
    if (pre[x][loc] == -1) {
        return ;
    }
    if (a1[x] == a2[loc]) {
        printAns(x - 1, pre[x][loc]);
        printf("%d ", a1[x]);
    }
    else {
        printAns(x - 1, loc);
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    int first = 1;
    while (test_case--) {
        if (!first) {
            printf("\n");
        }
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a1[i]);
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d", &a2[i]);
        }
        memset(dp, 0, sizeof(dp));
        memset(pre, -1, sizeof(pre));
        for (int i = 1; i <= n; i++) {
            int pre_j = 0;
            int cnt_max = 0;
            for (int j = 1; j <= m; j++) {
                dp[i][j] = dp[i - 1][j];
                pre[i][j] = j;
                if (a2[j] < a1[i] && cnt_max < dp[i - 1][j]) {
                    cnt_max = dp[i - 1][j];
                    pre_j = j;
                }
                if (a2[j] == a1[i]) {
                    dp[i][j] = cnt_max + 1;
                    pre[i][j] = pre_j;
                }
            }
        }
        int ans = -1;
        int loc;
        for (int i = 1; i <= m; i++) {
            if (dp[n][i] > ans) {
                ans = dp[n][i];
                loc = i;
            }
        }
        printf("%d\n", ans);
        printAns(n, loc);
        printf("\n");
        first = 0;
    }
    return 0;
}
