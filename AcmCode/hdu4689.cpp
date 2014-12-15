#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const long long mod = 1000000009ll;
const int maxn = 1000007;
//const int mod = 1000 * 1000 * 1000 + 9;

long long c[maxn];

long long powMod(long long a, long long b) {
    long long result = 1;
    long long cnt = a;
    while (b) {
        if (b & 1) {
            result = (result * cnt) % mod;
        }
        cnt = (cnt * cnt) % mod;
        b /= 2;
    }
    return result % mod;
}

int n, m;
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        int l = 0, r = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            int next_l = l;
            int next_r = r;
            if (l >= x) {
                next_l = l - x;
            }
            else if (r >= x) {
                next_l = ((x & 1) == (r & 1)) ? 0 : 1;
            }
            else {
                next_l = x - r;
            }
            if (x + r <= m) {
                next_r = x + r;
            }
            else if (l + x <= m) {
                next_r = ((m - l) & 1) ==  (x & 1) ? m : m - 1;
            }
            else {
                next_r = m - (x - (m - l));
            }
            l = next_l;
            r = next_r;
        }
        c[0] = 1;
        long long ans = 0;
        for (int i = 0; i <= r; i++) {
            if (i) {
                if (m - i < i) {
                    c[i] = c[m - i];
                }
                else {
                    c[i] = c[i - 1] * ((long long)(m - i + 1) * powMod(i, mod - 2) % mod) % mod;
                }
            }
            if (i >= l && (i & 1) == (l & 1)) {
                ans = (ans + c[i]) % mod;
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
