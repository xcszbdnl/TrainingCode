#include <cstdio>
#include <cstring>

const int maxn = 50;

long long dp[maxn][maxn];
int n;
int num[maxn];
int ans;
void solve() {
    int loc = 0;
    n++;
    while (n) {
        num[loc++] = n % 10;
        n /= 10;
    }
    ans = 0;
    for (int i = loc - 1; i >= 0; i--) {
        if (num[i] >= 2) {
            ans += dp[i + 1][1] + dp[i + 1][0];
            break;
        }
        else if (num[i] == 1) {
            ans += dp[i + 1][0];
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    dp[1][0] = 1;
    dp[1][1] = 1;
    for (int i = 2; i <= 10; i++) {
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
    }
    scanf("%d", &n);
    solve();
    printf("%d\n", ans - 1);
    return 0;
}
