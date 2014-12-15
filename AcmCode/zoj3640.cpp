#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 200007;
const double eps = 1e-12;
int f, n;
long long val[maxn];
long long day[maxn];
long long maxc;
double dp[maxn * 2];

int cal(int cnt_val) {
    return cnt_val * cnt_val * (1 + sqrt(5 + eps)) / 2.0;
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &f) != EOF) {
        memset(dp, 0, sizeof(dp));
        maxc = 0;
        double tot_day = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &val[i]);
            if (val[i] > maxc) {
                maxc = val[i];
            }
            day[i] = cal(val[i]);
            tot_day += day[i];
        }
        tot_day /= n;
        for (int i = maxc + 1; i <= 2 * maxc + 10; i++) {
            dp[i] = tot_day;
        }
        for (int i = maxc; i >= f; i--) {
            dp[i] = 0;
            for (int j = 1; j <= n; j++) {
                if (i > val[j]) {
                    dp[i] += day[j] * 1.0 / n;
                }
                else {
                    dp[i] += (dp[i + val[j]] + 1) * 1.0 / n;
                }
            }
        }
        printf("%.3f\n", dp[f]);
    }
    return 0;
}
