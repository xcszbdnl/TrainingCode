#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 507;
long long dp[maxn][maxn], ans;
int n;
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n - 2; i++) {
        dp[n - i][i] = 1;
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if (dp[i][j] != 0) {
                for (int s = j + 1; s <= i; s++) {
                    dp[i - s][s] += dp[i][j];
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
//        printf("dp%d:%d\n", i, dp[0][i]);
        ans += dp[0][i];
    }
    cout << ans << endl;
}
