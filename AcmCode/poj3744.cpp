#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int max_loc;
int n;
double p, a, b, c;
int loc[50];

struct Matrix {
    double a[5][5];
};


struct Matrix multi(struct Matrix a, struct Matrix b) {
    struct Matrix ret;
    for (int i = 1;i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            ret.a[i][j] = 0;
            for (int k = 1; k <= 2; k++) {
                ret.a[i][j] += a.a[i][k] * b.a[k][j];
            }
        }
    }
    return ret;
};
struct Matrix getMatrix(int k) {
    struct Matrix ret;
    ret.a[1][1] = ret.a[2][2] = 1.0;
    ret.a[1][2] = ret.a[2][1] = 0;
    struct Matrix power;
    power.a[1][1] = p;
    power.a[1][2] = 1 - p;
    power.a[2][1] = 1;
    power.a[2][2] = 0;
    while (k) {
        if (k & 1) {
            ret = multi(power, ret);
        }
        power = multi(power, power);
        k /= 2;
    }
    return ret;
};
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%lf", &n, &p) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &loc[i]);
        }
        a = 0;
        b = 1;
        loc[0] = 0;
        for (int i = 1; i  <= n; i++) {
            int k = loc[i] - loc[i - 1] - 1;
            struct Matrix result = getMatrix(k);
            double fn = result.a[1][1] * b + result.a[1][2] * a;
            double fn_1 = result.a[2][1] * b + result.a[2][2] * a;
            double fn_2 = fn_1 * (1 - p);
            a = 0;
            b = fn_2;
        }
        printf("%.7f\n", b);
    }
    return 0;
}
