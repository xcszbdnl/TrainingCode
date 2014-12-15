#include <cstdio>
#include <cstring>

int e, n, c;


int getPow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) {
            ret = (ret * a) % n;
        }
        a = (a * a) % n;
        b /= 2;
    }
    return ret;
}
void gcd(int a, int b, int &d, int &x, int &y) {
    if (!b) {
        d = a;
        x = 1;
        y = 0;
    }
    else {
        gcd(b, a % b, d, y, x);
        y -= (x * (a / b));
    }
}
int inv(int a, int n) {
    int d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n: -1;
}


int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d%d", &e, &n, &c);
        int ans, p, q;
        for (int i = 2; i < n; i++) {
            if (n % i == 0) {
                p = i;
                q = n / i;
                break;
            }
        }
        int fin = (p - 1) * (q - 1);
        int pow_num = inv(e, fin);
        ans = getPow(c, pow_num);
        printf("%d\n", ans);
    }
    return 0;
}
