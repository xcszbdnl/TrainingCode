#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;


const double pi = acos(-1.0);
const int maxn = 400007;
struct Complex {
    double a, b;
    Complex(){}
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

void brc(Complex *x, int n) {
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

struct Complex x_1[maxn], x_2[maxn];
char str_1[maxn], str_2[maxn];
int ans[maxn];
int main() {
    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    int ncase = 1;
    while (test_case--) {
        memset(ans, 0, sizeof(ans));
        scanf("%s%s", str_1, str_2);
        int len_1 = strlen(str_1);
        int len_2 = strlen(str_2);
        int tmp = max(len_1, len_2) << 1;
        int len = 1;
        while (len < tmp) {
            len <<= 1;
        }
        for (int j = 0; j < 26; j++) {
            for (int i = 0; i < len; i++) {
                x_1[i].a = x_2[i].a = x_1[i].b = x_2[i].b = 0;
            }
            for (int i = 0; i < len_1; i++) {
                if (str_1[i] == j + 'a') {
                    x_1[i].a = 1;
                }
            }
            for (int i = 0; i < len_2; i++) {
                if (str_2[len_2 - 1 - i] == j + 'a') {
                    x_2[i].a = 1;
                }
            }
            FFT(x_1, len, 1);
            FFT(x_2, len, 1);
            for (int i = 0; i < len; i++) {
                x_1[i] = x_1[i] * x_2[i];
            }
            FFT(x_1, len, -1);
            for (int i = 0; i < len_1; i++) {
                ans[i] += (int)(x_1[i + len_2 - 1].a + 0.5);
            }
        }
        int max_ans = -1;
        int loc = -1;
        for (int i = 0; i < len_1; i++) {
            if (len_2 - ans[i] <= 2) {
                loc = i;
                break;
            }
        }
        printf("Case #%d: %d\n", ncase, loc);
        ncase++;
    }
    return 0;
}
