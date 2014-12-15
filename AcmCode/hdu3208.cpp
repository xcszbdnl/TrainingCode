#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-8;
const double INF = 1e18+300;
const int maxn = 107;
const long long T = 1ll << 31;
int vis[maxn], prime[maxn], prime_num, val[maxn], len;
long long num[maxn];
long long a, b;

int sgn(double x) {
    return x < -eps ? -1 : x > eps;
}


void getAllPrime() {
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) {
            for (int j = i * i; j < maxn; j += i) {
                vis[j] = 1;
            }
        }
    }
    prime_num = 0;
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) {
            prime[++prime_num] = i;
        }
    }
}

long long multi(long long a, long long b) {
    long long ret = 1;
    while (b) {
        if (ret < 0) {
            return -1;
        }
        if (b & 1) {
            double judge = 1.0 * INF / ret;
            if (a > judge) {
                return -1;
            }
            ret *= a;
        }
        b >>= 1;
        if (a > T && b > 0) {
            return -1;
        }
        a *= a;
    }
    if (ret < 0) {
        return -1;
    }
    return ret;
}
long long getNum(long long n, long long cnt) {
    long long r = pow(n, 1.0 / cnt);
    long long t, p;
    p = multi(r, cnt);
    if (p == n) {
        return r;
    }
    if (p > n || p == -1) {
        r--;
    }
    else {
        t = multi(r + 1, cnt);
        if (t != -1 && t <= n) {
            r++;
        }
    }
    return r;
}

long long cal(long long n) {
    long long ret = 0;
    int k;
    num[1] = n;
    for (int i = 2; i <= 64; i++) {
//        double x = pow(n, 1.0 / i);
//        long long cnt_num = x + 0.5;
//        long long temp = 1;
//        for (int j = 1; j <= i; j++) {
//            temp = temp * cnt_num;
//            if (temp < 0) {
//                break;
//            }
//        }
//        if (temp > n || temp < 0) {
//            cnt_num--;
//        }
//        temp = 1;
//        for (int j = 1; j <= i; j++) {
//            temp = temp * cnt_num;
//            if (temp < 0) {
//                break;
//            }
//        }
//        if (temp > n || temp < 0) {
//            cnt_num--;
//        }
//        cnt_num--;
//        num[i] = cnt_num;
        num[i] = getNum(n, i) - 1;
        if (!num[i]) {
            k = i;
            break;
        }
    }
    for (int i = k - 1; i >= 0; i--) {
        for (int j = 1; j < i; j++) {
            if (i % j == 0) {
                num[j] -= num[i];
            }
        }
    }
    ret = num[1];
    for (int i = 2; i <= k - 1; i++) {
        ret += num[i] * i;
    }
    return ret;
}
int main() {
//    freopen("in.txt", "r", stdin);
    getAllPrime();
    while (scanf("%I64d%I64d", &a, &b) != EOF) {
        if (!a && !b) {
            break;
        }
        memset(num, 0, sizeof(num));
        long long ans_1 = cal(b);
        long long ans_2 = cal(a - 1);
        long long ans = ans_1 - ans_2;
        printf("%I64d\n", ans);
    }
    return 0;
}
