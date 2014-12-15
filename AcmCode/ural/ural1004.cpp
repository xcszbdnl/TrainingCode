#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 107;
const int INF = 10000007;
vector<int> result;
int maps[maxn][maxn];
int dp[maxn][maxn], pre[maxn][maxn];
int n, m, ans;

void floyd() {
    ans = INF;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                int temp = dp[i][j] + maps[j][k] + maps[k][i];
                if (temp < ans) {
                    ans = temp;
                    result.clear();
                    int cnt = j;
                    while (cnt != i) {
                        result.push_back(cnt);
                        cnt = pre[i][cnt];
                    }
                    result.push_back(i);
                    result.push_back(k);
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][j] > dp[i][k] + dp[k][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    pre[i][j] = pre[k][j];
                }
            }
        }
    }
}
int main() {
//    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        if (n == -1) {
            break;
        }
        scanf("%d", &m);
        for (int i = 1; i <= n; i++) {
            maps[i][i] = 0;
            dp[i][i] = 0;
            pre[i][i] = i;
            for (int j = i + 1; j <= n; j++) {
                maps[i][j] = maps[j][i] = INF;
                dp[i][j] = dp[j][i] = INF;
            }
        }
        for (int i = 1; i <= m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if (maps[a][b] > c || maps[b][a] > c) {
                maps[a][b] = maps[b][a] = dp[a][b] = dp[b][a] = c;
                pre[a][b] = a;
                pre[b][a] = b;
            }
        }
        floyd();
        if (ans == INF) {
            printf("No solution.\n");
        }
        else {
//            printf("%d\n", ans);
            for (int i = 0; i < result.size(); i++) {
                printf("%d%c", result[i], i != result.size() - 1?' ':'\n');
            }
        }
    }
    return 0;
}
