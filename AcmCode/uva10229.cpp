#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;

long long mod_number;
struct Matrix {
    long long value[3][3];
};

struct Matrix multiply(struct Matrix a, struct Matrix b) {
    struct Matrix result;
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            result.value[i][j] = 0;
            for (int k = 1; k <= 2; k++) {
                result.value[i][j] = (result.value[i][j] + a.value[i][k] * b.value[k][j]) % mod_number;
            }
        }
    }
    return result;
}

long long getMod(long long cnt_pow) {
    struct Matrix result;
    struct Matrix square;
    result.value[1][1] = result.value[2][2] = 1;
    result.value[1][2] = result.value[2][1] = 0;
    square.value[1][2] = square.value[2][1] = square.value[2][2] = 1;
    square.value[1][1] = 0;
    while (cnt_pow) {
        if (cnt_pow & 1) {
            result = multiply(result, square);
        }
        square = multiply(square, square);
        cnt_pow >>= 1;
    }
    return result.value[1][2];
}

long long n;
int m;
int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%lld%d", &n, &m) != EOF) {
        mod_number = (1ll << m);
        long long ans = getMod(n);
        printf("%lld\n", ans);
    }
    return 0;
}
