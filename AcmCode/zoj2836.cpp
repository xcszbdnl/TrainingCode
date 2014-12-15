#include <cstdio>
#include <cstring>
#include <cstring>

const int maxn = 17;
int n, m, val[maxn];
long long ans;

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &val[i]);
        }
        ans = 0;
        for (int i = 1; i < (1 << n); i++) {
            long long lcm = 1;
            int c = 0;
            for (int j = 0; j < n; j++) {
                if ((1 << j) & i) {
                    c++;
                    long long temp = gcd(lcm, val[j]);
                    lcm /= temp;
                    long long x = val[j];
                    lcm *= x;
                }
            }
            if (c % 2) {
                ans += m / lcm;
            }
            else {
                ans -= m / lcm;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
