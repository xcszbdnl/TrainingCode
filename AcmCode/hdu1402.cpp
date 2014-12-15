#include <cstdio>
#include <cstring>
#include <cmath>
#include <stack>
#include <algorithm>

using namespace std;
const double pi = acos(-1.0);
const double eps = 1e-6;
const int maxn = 300007;


struct Complex {
    double a, b;
    Complex() {
    }
    Complex(double a, double b): a(a), b(b) {
    }
    Complex operator +(const Complex &x) const {
        return Complex(a + x.a, b + x.b);
    }
    Complex operator -(const Complex &x) const {
        return Complex(a - x.a, b - x.b);
    }
    Complex operator *(const Complex &x) const {
        return Complex(a * x.a - b * x.b, a * x.b + b * x.a);
    }
};
char str_1[maxn], str_2[maxn];
Complex x_1[maxn], x_2[maxn];
stack<int> ans;

//二进制反转
void brc(Complex *x, int n) {
    int i, j, k;
    for (int i = 1, j = (n >> 1); i < n - 1; i++) {
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

//on == 1是正变换，on == -1是逆变换
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

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%s%s", str_1, str_2) != EOF) {
        int len_1 = strlen(str_1);
        int len_2 = strlen(str_2);
        int tmp = max(len_1, len_2) << 1;
        int n = 1;
        while (n < tmp) {
            n <<= 1;
        }
        for (int i = 0; i < n; i++) {
            x_1[i].a = x_1[i].b = x_2[i].a = x_2[i].b = 0;
        }
        for (int i = 0; i < len_1; i++) {
            x_1[i].a = str_1[len_1 - i - 1] - '0';
        }
        for (int i = 0; i < len_2; i++) {
            x_2[i].a = str_2[len_2 - i - 1] - '0';
        }
        FFT(x_1, n, 1);
        FFT(x_2, n, 1);
        for (int i = 0; i < n; i++) {
            x_1[i] = x_1[i] * x_2[i];
        }
        FFT(x_1, n, -1);
        while (!ans.empty()) {
            ans.pop();
        }
        int pre = 0;
        for (int i = 0; i < len_1 + len_2 || pre; i++) {
            int cnt = (int)(x_1[i].a + 0.5);
            cnt = cnt + pre;
            ans.push(cnt % 10);
            pre = cnt / 10;
        }
        while (!ans.empty() && ans.top() == 0) {
            ans.pop();
        }
        if (ans.empty()) {
            puts("0");
        }
        else {
            while (!ans.empty()) {
                printf("%d", ans.top());
                ans.pop();
            }
            printf("\n");
        }
    }
    return 0;
}
