#include <cstdio>
#include <string.h>
int row;
int k, mod_number;
struct Matrix {
    int value[35][35];
    void print() {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= row; j++) {
                if (j == 1) {
                    printf("%d", value[i][j]);
                }
                else {
                    printf(" %d", value[i][j]);
                }
            }
            printf("\n");
        }
    }
};


struct Matrix input;


struct Matrix add(struct Matrix a, struct Matrix b) {
    struct Matrix result;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= row; j++) {
            result.value[i][j] = (a.value[i][j] + b.value[i][j]) % mod_number;
        }
    }
    return result;
}

struct Matrix multiply(struct Matrix a, struct Matrix b) {
    struct Matrix result;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= row; j++) {
            result.value[i][j] = 0;
            for (int k = 1; k <= row; k++) {
                result.value[i][j] += (a.value[i][k] * b.value[k][j]) % mod_number;
                result.value[i][j] %= mod_number;
            }
        }
    }
    return result;
}

struct Matrix get(int cnt_pow) {
    struct Matrix result;
    struct Matrix square = input;
    for (int i = 1; i <= row; i++) {
        result.value[i][i] = 1;
        for (int j = i + 1; j <= row; j++) {
            result.value[i][j] = result.value[j][i] = 0;
        }
    }
    while (cnt_pow) {
        if (cnt_pow & 1) {
            result = multiply(result, square);
        }
        square = multiply(square, square);
        cnt_pow >>= 1;
    }
    return result;
}

struct Matrix getMod(int cnt_pow) {
    if (cnt_pow == 1) {
        return input;
    }
    struct Matrix x = getMod(cnt_pow / 2);
    struct Matrix pow_matrix;
    if (cnt_pow & 1) {
        pow_matrix = get(cnt_pow / 2 + 1);
        struct Matrix temp = pow_matrix;
        pow_matrix = multiply(pow_matrix, x);
        x = add(x, pow_matrix);
        x = add(x, temp);
    }
    else {
        pow_matrix = get(cnt_pow / 2);
        pow_matrix = multiply(pow_matrix, x);
        x = add(x, pow_matrix);
    }
    /*
    pow_matrix = get(cnt_pow / 2);
    pow_matrix = multiply(x, pow_matrix);
    x = add(x, pow_matrix);
    if (cnt_pow & 1) {
        pow_matrix = get(cnt_pow);
        x = add(x, cnt_pow);
    }
    */
    return x;
}

int main() {

    scanf("%d%d%d", &row, &k, &mod_number);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= row; j++) {
            scanf("%d", &input.value[i][j]);
        }
    }
    struct Matrix ans;
    ans = getMod(k);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= row; j++) {
            if (j == 1) {
                printf("%d", ans.value[i][j]);
            }
            else {
                printf(" %d", ans.value[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}
