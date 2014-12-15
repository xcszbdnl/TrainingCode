#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;


const int maxn = 100011;
int mobius[maxn];
int vis[maxn];

void getMobius() {
    memset(mobius, 0, sizeof(mobius));
    memset(vis, 0, sizeof(vis));
    mobius[1] = 1;
    for (int i = 2; i < maxn ; i++) {
        if (!vis[i]) {
            for (int j = i; j < maxn; j += i) {
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
long long n, m;

int main() {
//    freopen("in.txt", "r", stdin);
    getMobius();
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%I64d%I64d", &n, &m);
        int max_n = max(n, m);
        long long ans = 0;
        for (int i = 1; i <= max_n; i++) {
            ans += mobius[i] * (n / i) * (m / i);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
