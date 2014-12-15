#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

struct Matrix {
    long long a[3][3];
};


struct Matrix mul(struct Matrix a, struct Matrix b) {
    struct Matrix ret;
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            ret.a[i][j] = 0;
            for (int k = 1; k <= 2; k++) {
                ret.a[i][j] += a.a[i][k] * b.a[k][j];
            }
        }
    }
    return ret;
};

struct Matrix getPow(int pow_num) {
    struct Matrix ret;
    ret.a[1][1] = ret.a[2][2] = 1;
    ret.a[1][2] = ret.a[2][1] = 0;
    struct Matrix a;
    a.a[1][1] = a.a[1][2] = a.a[2][1] = 1;
    a.a[2][2] = 0;
    while (pow_num) {
        if (pow_num & 1) {
            ret = mul(ret, a);
        }
        a = mul(a, a);
        pow_num /= 2;
    }
    return ret;
};

long long i, fi, j, fj, n;
int main() {
    freopen("in.txt", "r", stdin);
    cin >> i >> fi >> j >> fj >> n;
    if (i > j) {
        swap(i, j);
        swap(fi, fj);
    }
    int cnt_pow = j - i - 1;
    struct Matrix ret;
    ret = getPow(cnt_pow);
    long long fi_1 = (fj - ret.a[1][2] * fi) / ret.a[1][1];
    if (n < i) {
        long long a = fi_1;
        long long b = fi;
        long long c;
        for (int k = i - 1; k >= n; k--) {
            c = a - b;
            a = b;
            b = c;
        }
        cout << b << endl;
    }
    else if (n > i) {
        long long a = fi;
        long long b = fi_1;
        long long c;
        for (int k = i + 2; k <= n; k++) {
            c = a + b;
            a = b;
            b = c;
        }
        cout << b << endl;
    }
    else {
        cout << fi << endl;
    }
    return 0;
}
