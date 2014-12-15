#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 1007;

struct P {
    int x, y;
    bool operator < (const struct P &a) const {
        if (x == a.x) {
            return y < a.y;
        }
        return x < a.x;
    }
};

struct P p[maxn];
int dp[maxn];
int n, m, k;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    sort(p + 1, p + 1 + k);
    dp[k] = 1;
    for (int i = k - 1; i >= 1; i--) {
        dp[i] = 1;
        for (int j = i + 1; j <= k; j++) {
            if (p[j].x > p[i].x && p[j].y > p[i].y) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int max_num = 0;
    for (int i = 1; i <= k; i++) {
        max_num = max(max_num, dp[i]);
    }
    double ans = max_num * 100 * sqrt(2.0);
    ans = ans + (n - max_num) * 100 + (m - max_num) * 100;
    long long ret = ans + 0.5;
    printf("%I64d\n", ret);
    return 0;
}
