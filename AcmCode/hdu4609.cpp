#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 400007;
const double pi = acos(-1.0);
struct Complex {
    double a, b;
    Complex() {}
    Complex(double a, double b): a(a), b(b){}
    Complex operator + (const struct Complex &x) const {
        return Complex(a + x.a, b + x.b);
    }
    Complex operator - (const struct Complex &x) const {
        return Complex(a - x.a, b - x.b);
    }
    Complex operator * (const struct Complex &x) const {
        return Complex(a * x.a - b * x.b, a * x.b + b * x.a);
    }
};

Complex x_1[maxn], x_2[maxn];
long long num[maxn], sum[maxn];
int len;

void brc(struct Complex *x, int n) {
    int i, j, k;
    for (i = 1, j = (n >> 1); i < n - 1; i++) {
        if (i < j) {
            swap(x[i], x[j]);
        }
        k = n >> 1;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        if (j < k) {
            j += k;
        }
    }
}


void FFT(Complex *x, int n, int on) {
    int h, i, j, k, p;
    double r;
    Complex u, t;
    brc(x, n);
    for (h = 2; h <= n; h <<= 1) {
        r = on * 2.0 * pi / h;
        Complex wn(cos(r), sin(r));
        p = h >> 1;
        for (j = 0; j < n; j += h) {
            Complex w(1, 0);
            for (k = j; k < j + p; k++) {
                u = x[k];
                t = w * x[k + p];
                x[k] = u + t;
                x[k + p] = u - t;
                w = w * wn;
            }
        }
    }
    if (on == -1) {
        for (int i = 0; i < n; i++) {
            x[i].a = x[i].a / n;
        }
    }
}
int tot, n;
int val[maxn];
int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &n);
        tot = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            tot = max(val[i], tot);
        }
        tot++;
        sort(val + 1, val + 1 + n);
        tot <<= 1;
        int len = 1;
        while (len < tot) {
            len <<= 1;
        }
        for (int i = 0; i <= len; i++) {
            x_1[i].a = x_1[i].b = x_2[i].a = x_2[i].b = 0;
        }
        for (int i = 1; i <= n; i++) {
            x_1[val[i]].a += 1;
            x_2[val[i]].a += 1;
        }
        FFT(x_1, len, 1);
        FFT(x_2, len, 1);
        for (int i = 0; i < len; i++) {
            x_1[i] = x_1[i] * x_2[i];
        }
        FFT(x_1, len, -1);
        for (int i = 0; i <= len; i++) {
            num[i] = (int)(x_1[i].a + 0.5);
        }
        for (int i = 1; i <= n; i++) {
            num[val[i] * 2]--;
        }
        for (int i = 0; i <= len; i++) {
            num[i] /= 2;
        }
        sum[0] = 0;
        for (int i = 1; i <= len; i++) {
            sum[i] = sum[i - 1] + num[i];
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += sum[len] - sum[val[i]];
            ans -= (long long)(i - 1) * (n - i);
            ans -= (long long)(n - i) * (n - i - 1) / 2;
            ans -= (long long)(n - 1);
        }
        long long tot = (long long)n * (n - 1) * (n - 2) / 6;
        double result = ans * 1.0 / tot;
        printf("%.7f\n", result);
    }
    return 0;
}
