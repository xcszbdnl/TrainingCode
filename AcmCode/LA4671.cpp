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

Complex x_1[maxn], x_2[maxn];
char str_1[maxn], str_2[maxn];
int ans[maxn], k;
int head[maxn], next[maxn], vis[maxn], len_1, len_2;


int judgeEqual(int start_1, int start_2) {
    for (int i = 0; i < len_2; i++) {
        if (str_1[start_1 + i] !=  str_1[start_2 + i]) {
            return 0;
        }
    }
    return 1;
}
void judgeDiff() {
    memset(vis, 0, sizeof(vis));
    long long h = 1;
    for (int i = 1; i <= len_2 - 1; i++) {
        h = (h * 2) % maxn;
    }
    int hash_num = 0;
    for (int i = 0; i < len_2; i++) {
        hash_num = (hash_num * 2) % maxn;
        if (str_1[i] == 'b') {
            hash_num = (hash_num + 1) % maxn;
        }
    }
    vis[0] = 1;
    head[hash_num] = 0;
    for (int i = 1; i < len_1 - len_2 + 1; i++) {
        int flag = str_1[i - 1] == 'b' ? 1 : 0;
        hash_num = (((hash_num - h * flag) % maxn) + maxn) % maxn;
        hash_num = (hash_num * 2) % maxn;
        if (str_1[i + len_2 - 1] == 'b') {
            hash_num = (hash_num + 1) % maxn;
        }
        int u = head[hash_num];
        while (u != -1 && !judgeEqual(u, i)) {
            u = next[u];
        }
        if (u == -1) {
            vis[i] = 1;
            next[i] = head[hash_num];
            head[hash_num] = i;
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    int ncase = 1;
    while (1) {
        memset(ans, 0, sizeof(ans));
        memset(head, -1, sizeof(head));
        memset(vis, -1, sizeof(vis));
        scanf("%d", &k);
        if (k == -1) {
            break;
        }
        scanf("%s%s", str_1, str_2);
        len_1 = strlen(str_1);
        len_2 = strlen(str_2);
        int tmp = max(len_1, len_2) << 1;
        int n = 1;
        while (n < tmp) {
            n <<= 1;
        }
        judgeDiff();
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < n; i++) {
                x_1[i].a = x_1[i].b = x_2[i].a = x_2[i].b = 0;
            }
            for (int i = 0; i < len_1; i++) {
                if (str_1[i] == 'a' + j) {
                    x_1[i].a = 1;
                }
            }
            for (int i = 0; i < len_2; i++) {
                if (str_2[len_2 - 1 - i] == 'a' + j) {
                    x_2[i].a = 1;
                }
            }
            FFT(x_1, n, 1);
            FFT(x_2, n, 1);
            for (int i = 0; i < n; i++) {
                x_1[i] = x_1[i] * x_2[i];
            }
            FFT(x_1, n, -1);
            for (int i = 0; i < len_1; i++) {
                ans[i] += (long long)(x_1[i + len_2 - 1].a + 0.5);
            }
        }
        int result = 0;
        for (int i = 0; i < len_1 - len_2 + 1; i++) {
            if (len_2 - ans[i] <= k && vis[i]) {
                result++;
            }
        }
        printf("Case %d: %d\n", ncase, result);
        ncase++;
    }
    return 0;
}
