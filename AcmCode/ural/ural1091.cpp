#include <cstdio>
#include <cstring>
#include <cmath>

const int maxn = 10007;
int prime[maxn], prime_num, vis[maxn], mobius[maxn];
long long com[100][100];
long long f[maxn];
int k, s;

void getMobius() {
    memset(vis, 0, sizeof(vis));
    memset(mobius, 0, sizeof(mobius));
    mobius[1] = 1;
    for (int i = 2; i < maxn; i++) {
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
        else {
            if (mobius[i] % 2) {
                mobius[i] = -1;
            }
            else {
                mobius[i] = 1;
            }
        }
    }
}
void getCom() {
    for (int i = 0; i <= 30; i++) {
        com[i][0] = com[i][i] = 1;
        for (int j = 1; j < i; j++) {
            com[i][j] = com[i - 1][j - 1] + com[i - 1][j];
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    getMobius();
    getCom();
    memset(f, 0, sizeof(f));
    scanf("%d%d", &k, &s);
    long long ans = 0;
    for (int i = 2; i <= s; i++) {
        for (int j = 1; i * j <= s; j++) {
            int cnt = i * j;
            int g = com[s / cnt][k];
            f[i] += mobius[j] * g;
        }
    }
    for (int i = 2; i <= s; i++) {
        ans += f[i];
        if (ans > 10000) {
            break;
        }
    }
    if (ans > 10000) {
        ans = 10000;
    }
    printf("%I64d\n", ans);
    return 0;
}
