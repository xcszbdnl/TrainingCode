#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const double pi = acos(-1.0);
const int maxn = (1 << 20) + 7;
const long long INF = 1000000007ll;
struct Complex {
    double a, b;
    Complex() {};
    Complex(double a, double b): a(a), b(b){};
    inline Complex operator + (const struct Complex &x) const {
        return Complex(a + x.a, b + x.b);
    }
    inline Complex operator - (const struct Complex &x) const {
        return Complex(a - x.a, b - x.b);
    }
    inline Complex operator * (const struct Complex &x) const {
        return Complex(a * x.a - b * x.b, a * x.b + b * x.a);
    }
};

struct Complex x_1[maxn], x_2[maxn];
int next[maxn], val_1[maxn], val_2[maxn];
long long ans[maxn];
int n, m;
vector<int> ans_loc;
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


int judgeEqual(int a, int b) {
    if (a == b) {
        return 1;
    }
    if ((a ^ 1) == b) {
        return 1;
    }
    if (a == (b ^ 1)) {
        return 1;
    }
    return 0;
}

void getNext() {
    next[0] = -1;
    int k = -1;
    for (int i = 1; i < m; i++) {
        while (k != -1 && !judgeEqual(val_2[k + 1], val_2[i])) {
            k = next[k];
        }
        if (judgeEqual(val_2[k + 1], val_2[i])) {
            k++;
        }
        next[i] = k;
    }
}

void match() {
    int k = -1;
    for (int i = 0; i < n; i++) {
        while (k > -1 && !judgeEqual(val_2[k + 1], val_1[i])) {
            k = next[k];
        }
        if (judgeEqual(val_2[k + 1], val_1[i])) {
            k++;
        }
        if (k == m - 1) {
            ans_loc.push_back(i - m + 1);
            k = next[m - 1];
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < n; i++) {
        char temp[10];
        scanf("%s", temp);
        int num = 0;
        for (int j = 0; j < 8; j++) {
            num = (num << 1) + temp[j] - '0';
        }
        val_1[i] = num;
    }
    for (int i = 0; i < m; i++) {
        char temp[10];
        scanf("%s", temp);
        int num = 0;
        for (int j = 0; j < 8; j++) {
            num = (num << 1) + temp[j] - '0';
        }
        val_2[i] = num;
    }
    getNext();
    match();
    if (ans_loc.size() == 0) {
        puts("No");
        return 0;
    }
    int tmp = max(n, m) << 1;
    int len = 1;
    while (len < tmp) {
        len <<= 1;
    }
    for (int i = 0; i < len; i++) {
        x_1[i].a = x_1[i].b = x_2[i].a = x_2[i].b = 0;
    }
    for (int i = 0; i < n; i++) {
        x_1[i].a = val_1[i] % 2;
    }
    for (int i = 0; i < m; i++) {
        x_2[i].a = val_2[m - 1 - i] % 2;
    }
    FFT(x_1, len, 1);
    FFT(x_2, len, 1);
    for (int i = 0; i < len; i++) {
        x_1[i] = x_1[i] * x_2[i];
    }
    FFT(x_1, len, -1);
    for (int i = 0; i < n; i++) {
        ans[i] = (long long)(x_1[i + m - 1].a + 0.5);
    }
    for (int i = 0; i < len; i++) {
        x_1[i].a = x_1[i].b = x_2[i].a = x_2[i].b = 0;
    }
    for (int i = 0; i < n; i++) {
        x_1[i].a = 1 - (val_1[i] % 2);
    }
    for (int i = 0; i < m; i++) {
        x_2[i].a = 1 - (val_2[m - 1 - i] % 2);
    }
    FFT(x_1, len, 1);
    FFT(x_2, len, 1);
    for (int i = 0; i < len; i++) {
        x_1[i] = x_1[i] * x_2[i];
    }
    FFT(x_1, len, -1);
    long long min_ans = INF;
    int loc = 0;
    for (int i = 0; i < n; i++) {
        ans[i] += (long long)(x_1[i + m - 1].a + 0.5);
        ans[i] = m - ans[i];
    }
    for (int i = 0; i < ans_loc.size(); i++) {
        int cnt_loc = ans_loc[i];
        if (ans[cnt_loc] < min_ans) {
            min_ans = ans[cnt_loc];
            loc = cnt_loc;
        }
    }
    puts("Yes");
    printf("%I64d %d\n", min_ans, loc + 1);
    return 0;
}
