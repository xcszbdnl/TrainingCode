#include <cstdio>
#include <cstring>

const int maxn = 10007;

double p[maxn];
double a[maxn], b[maxn];
int k1, k2, k3, n, a1, b1, c1;
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d%d%d%d%d%d", &n, &k1, &k2, &k3, &a1, &b1, &c1);
//        printf("%d %d %d %d %d %d %d\n", n, k1, k2, k3, a1, b1, c1);
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(p, 0, sizeof(p));
        for (int i = 1; i <= k1; i++) {
            for (int j = 1; j <= k2; j++) {
                for (int k = 1; k <= k3; k++) {
                    if (i == a1 && j == b1 && k == c1) {
                        continue;
                    }
                    int s = i + j + k;
                    p[s] += 1.0 / (k1 * k2 * k3);
                }
            }
        }
        for (int i = n; i >= 0; i--) {
            double cnt_a = 0;
            double cnt_b = 0;
            for (int k = 1; k <= k1 + k2 + k3; k++) {
                cnt_a += p[k] * a[i + k];
                cnt_b += p[k] * b[i + k];
            }
            a[i] = cnt_a + 1.0 / (k1 * k2 * k3);
            b[i] = cnt_b + 1.0;
        }
        double ans = b[0] / (1 - a[0]);
        printf("%.15f\n", ans);
    }
    return 0;
}
