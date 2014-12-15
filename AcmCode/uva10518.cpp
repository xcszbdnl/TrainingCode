#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;
struct Matrix {
    int value[2][2];
};
long long n;
int base;

struct Matrix multiply(struct Matrix a, struct Matrix b) {
    struct Matrix result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result.value[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                int temp = (a.value[i][k] * b.value[k][j]) % base;
                result.value[i][j] = (result.value[i][j] + temp) % base;
            }
        }
    }
    return result;
}

int getMod() {
    struct Matrix square;
    square.value[0][0] = 1;
    square.value[0][1] = 1;
    square.value[1][0] = 1;
    square.value[1][1] = 0;
    struct Matrix result;
    result.value[0][0] = 1;
    result.value[0][1] = 1;
    result.value[1][0] = 1;
    result.value[1][1] = 1;
    while (n) {
        if (n & 1) {
            result = multiply(result, square);
        }
        square = multiply(square, square);
        n >>= 1;
    }
    return result.value[0][1] % base;
}

int main() {

    int case_number = 1;
    while (scanf("%lld%d", &n, &base) != EOF) {
        if (!n && !base) {
            break;
        }
        long long temp = n;
        int ans = getMod();
        ans = (2 * ans - 1 + base) % base;
        printf("Case %d: %lld %d %d\n", case_number, temp, base, ans);
        case_number++;
    }
    return 0;
}
