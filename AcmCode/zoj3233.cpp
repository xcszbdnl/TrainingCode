#include <cstdio>
#include <cstring>

const int maxn = 1007;

int bln[maxn], bun[maxn];
long long low, high, l, u, u_lcm;

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}


long long getLcm(long long a, long long b) {
    double t = (double)a * b;
    long long com = gcd(a, b);
    a /= com;
    long long temp = a * b;
    if (temp < 0 || temp / b != a) {
        return high + 1;
    }
    t /= com;
    if (t > high) {
        return high + 1;
    }
    a *= b;
    return a;
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%I64d%I64d%I64d%I64d", &l, &u, &low, &high) != EOF) {
        if (!l && !u && !low && !high) {
            break;
        }
        for (int i = 1; i <= l; i++) {
            scanf("%d", &bln[i]);
        }
        for (int i = 1; i <= u; i++) {
            scanf("%d", &bun[i]);
        }
        u_lcm = 1;
        int flag = 0;
        for (int i = 1; i <= u; i++) {
            u_lcm = getLcm(u_lcm, bun[i]);
        }
        long long ans_1 = 0;
        for (int i = 1; i < (1 << l); i++) {
            long long cnt_lcm = 1;
            int c = 0;
            for (int j = 0; j < l; j++) {
                if ((1 << j) & i) {
                    c++;
                    cnt_lcm = getLcm(cnt_lcm, bln[j + 1]);
                }
            }
            if (c % 2) {
                ans_1 += high  / cnt_lcm - (low - 1) / cnt_lcm;
            }
            else {
                ans_1 -= high  / cnt_lcm - (low - 1) / cnt_lcm;
            }
        }
        long long ans_2 = 0;
        for (int i = 1; i < (1 << l); i++) {
            long long cnt_lcm = 1;
            int c = 0;
            for (int j = 0; j < l; j++) {
                if ((1 << j) & i) {
                    c++;
                    cnt_lcm = getLcm(cnt_lcm, bln[j + 1]);
                }
            }
            cnt_lcm = getLcm(cnt_lcm, u_lcm);
            if (c % 2) {
                ans_2 += high  / cnt_lcm - (low - 1) / cnt_lcm;
            }
            else {
                ans_2 -= high  / cnt_lcm - (low - 1) / cnt_lcm;
            }
        }
//        printf("%I64d %I64d\n", ans_1, ans_2);
        printf("%I64d\n", ans_1 - ans_2);
    }
    return 0;
}
