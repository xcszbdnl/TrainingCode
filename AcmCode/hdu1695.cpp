#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100007;

int vis[maxn], mobius[maxn];

void getMobius() {
    memset(vis, 0, sizeof(vis));
    memset(mobius, 0, sizeof(mobius));
    mobius[1] = 1;
    for (int i = 2; i < maxn ; i++) {
        if (!vis[i]) {
            for (int j = i; j < maxn ; j += i) {
                vis[j] = 1;
                if (mobius[j] == -1) {
                    continue;
                }
                if ((j / i) % i == 0) {
                    mobius[j] = -1;
                }
                else {
                    mobius[j]++;
                }
            }
        }
    }
    for (int i = 2; i < maxn; i++) {
        if (mobius[i] == -1) {
            mobius[i] = 0;
        }
        else if (mobius[i] % 2) {
            mobius[i] = -1;
        }
        else {
            mobius[i] = 1;
        }
    }
}
int a, b, c, d, k;
int main() {
//    freopen("in.txt", "r", stdin);
    getMobius();
    int test_case;
    scanf("%d", &test_case);
    int ncase = 1;
    while (test_case--) {
        printf("Case %d: ", ncase++);
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        if (k == 0) {
            printf("0\n");
            continue;
        }
        b /= k;
        d /= k;
        int max_n = max(d, b);
        int min_n = min(d, b);
        long long ans = 0;
        for (int i = 1; i <= max_n; i++) {
            ans += mobius[i] * (long long)(d / i) * (long long)(b / i);
        }
        long long repeat = 0;
        for (int i = 1; i <= min_n; i++) {
            repeat += mobius[i] * (long long)(min_n / i) * (long long)(min_n / i);
        }
        printf("%I64d\n", ans - repeat / 2);
    }
    return 0;
}
