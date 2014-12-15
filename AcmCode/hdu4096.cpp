#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = (1 << 20) + 7;
const int mod = 1000 * 1000 * 1000 + 7;
long long dp[maxn];
int n, k, l;

int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d%d", &n, &k, &l);
        memset(dp, 0, sizeof(dp));
        int another = l - k;
        another++;
        int max_k = (1 << k);
        if (another < 0) {
            another = 1;
        }
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = max_k - 1; j >= 0; j--) {
                if (dp[j] != 0) {
                    long long temp = (dp[j] * another) % mod;
                    long long cnt_dp = dp[j];
                    dp[j] = 0;
                    for (int s = 1; s <= min(l, k); s++) {
                        int next_state = j | ((j << s)  & (max_k - 1)) | (1 << (s - 1));
                        dp[next_state] = (dp[next_state] + cnt_dp) % mod;
                    }
                    dp[j] += temp;
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < max_k; i++) {
            if (i & (1 << (k - 1))) {
                ans = (ans + dp[i]) % mod;
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
