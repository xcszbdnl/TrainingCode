#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;

const int maxn = 107;
const int INF = 10000007;

int dp[maxn][maxn][maxn];
int sum[maxn][maxn][maxn];
int n, k, vis[maxn][maxn];
int getAbs(int x) {
    return x < 0 ? -x : x;
}
int main() {
//    freopen("in.txt", "r", stdin);
    memset(vis, 0, sizeof(vis));
    memset(sum, 0, sizeof(sum));
    scanf("%d%d", &n, &k);
    int xc = k / 2 + 1;
    int yc = k / 2 + 1;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j][j - 1] = 0;
            sum[i][j][j - 1] = 0;
            for (int s = j; s <= k; s++) {
                dp[i][j][s] = dp[i][j][s - 1] + getAbs(i - xc) + getAbs(s - yc);
                sum[i][j][s] = sum[i][j][s - 1] + 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        int cnt_k;
        scanf("%d", &cnt_k);
        int min_ans, row, col;
        min_ans = INF;
        for (int j = 1; j <= k; j++) {
            for (int s = 1; s <= k - cnt_k + 1; s++) {
                if (sum[j][s][s + cnt_k - 1] != cnt_k) {
                    continue;
                }
                if (dp[j][s][s + cnt_k - 1] < min_ans) {
                    min_ans = dp[j][s][s + cnt_k - 1];
                    row = j;
                    col = s;
                }
                else if (dp[j][s][s + cnt_k - 1] == min_ans) {
                    if (j < row) {
                        row = j;
                        col = s;
                    }
                    else if (j == row) {
                        if (s < col) {
                            col = s;
                        }
                    }
                }
            }
        }
        if (min_ans == INF) {
            puts("-1");
            continue;
        }
        printf("%d %d %d\n", row, col, col + cnt_k - 1);
        for (int j = col; j <= col + cnt_k - 1; j++) {
            vis[row][j] = 1;
        }
        for (int j = 1; j <= k; j++) {
            sum[row][j][j - 1] = 0;
            for (int s = j; s <= k; s++) {
                if (vis[row][s]) {
                    sum[row][j][s] = sum[row][j][s - 1];
                }
                else {
                    sum[row][j][s] = sum[row][j][s - 1] + 1;
                }
            }
        }
    }
    return 0;
}
