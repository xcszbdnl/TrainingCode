#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10007;
int val[maxn], vis[30];
long long n, m;

bool cmp(int a, int b) {
    return a > b;
}

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%I64d%I64d", &n, &m) != EOF) {
//        int flag = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d", &val[i]);
        }
        sort(val, val + m, cmp);
        while (!val[m - 1]) {
            m--;
        }
//        memset(vis, 0, sizeof(vis));
//        for (int i = 0; i < m; i++) {
//            for (int j = i + 1; j < m; j++) {
//                if (val[i] % val[j] == 0) {
//                    vis[i] = 1;
//                }
//            }
//        }
//        int len = 0;
//        for (int i = 0; i < m; i++) {
//            if (!vis[i]) {
//                val[len++] = val[i];
//            }
//        }
        long long ans = 0;
        n--;
        for (int i = 1; i < (1 << m); i++) {
            int c = 0;
            long long k = 1;
            for (int j = 0; j < m; j++) {
                if ((1 << j) & i) {
                    long long com = gcd(k, val[j]);
                    k = k * val[j];
                    k /= com;
                    c++;
                }
            }
            if (c % 2) {
                ans += n / k;
            }
            else {
                ans -= n / k;
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}

