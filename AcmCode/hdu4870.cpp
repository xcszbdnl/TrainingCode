#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 250;
const double eps = 1e-10;
double matrix[maxn][maxn];
int num[30][30], loc;
double p;

int gauss(int equ, int var) {
    int i = 0, j = 0;
    while (j < equ && i < var) {
        int r = i;
        for (int k = i + 1; k < equ; k++) {
            if (fabs(matrix[k][j]) > fabs(matrix[r][j])) {
                r = k;
            }
        }
        if (r != i) {
            for (int k = j; k <= var; k++) {
                swap(matrix[i][k], matrix[r][k]);
            }
        }
        if (fabs(matrix[i][j]) < eps) {
            j++;
            continue;
        }
        for (int k = i + 1; k < equ; k++) {
            if (fabs(matrix[k][j]) > eps) {
                double f =  matrix[k][j] / matrix[i][j];
                for (int s = j; s <= var; s++) {
                    matrix[k][s] -= f * matrix[i][s];
                }
            }
        }
        i++;
        j++;
    }
    int ret = equ - i;
    for (int k = i; k < equ; k++) {
        if (fabs(matrix[k][var]) > eps) {
            return -1;
        }
    }
    for (int i = equ - 1; i >= 0; i--) {
        if (fabs(matrix[i][i]) < eps) {
            continue;
        }
        for (int j = i + 1; j < var; j++) {
            matrix[i][loc] -= matrix[j][var] * matrix[i][j];
        }
        matrix[i][var] /= matrix[i][i];
    }
    return ret;
}
int main() {
//    freopen("in.txt", "r", stdin);
//    memset(matrix, 0, sizeof(matrix));
//    scanf("%lf", &p);
    memset(num, 0, sizeof(num));
    loc = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j <= i; j++) {
            num[i][j] = loc++;
        }
    }
    while (scanf("%lf", &p) != EOF) {
        memset(matrix, 0, sizeof(matrix));
        int var = loc, equ = loc;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < i; j++) {
                int cnt_loc = num[i][j];
                matrix[cnt_loc][cnt_loc] = 1;
                matrix[cnt_loc][loc] = 1;
                matrix[cnt_loc][num[i][j + 1]] -= p;
                matrix[cnt_loc][num[i][max(0,j - 2)]] -= (1 - p);
            }
            int cnt_loc = num[i][i];
            matrix[cnt_loc][cnt_loc] = 1;
            matrix[cnt_loc][loc] = 1;
            if (i + 1 != 20) {
                matrix[cnt_loc][num[i + 1][i]] -= p;
            }
            matrix[cnt_loc][num[i][max(0,i - 2)]] -= (1 - p);
        }
        gauss(equ, var);
        printf("%.6f\n", matrix[0][loc]);
    }
    return 0;
}
