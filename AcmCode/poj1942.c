#include <stdio.h>

double row, column;

int main() {

    double large, small, method;
    long long i;
    while (scanf("%lf%lf", &row, &column) != EOF) {
        if (!row && !column) {
            break;
        }
        if (row < column) {
            large = column;
            small = row;
        }
        else {
            large = row;
            small = column;
        }
        method = 1;
        for (i = 1; i <= small; i++) {
            method = method * (i + large) / i;
        }
        printf("%.0lf\n", method);
    }
    return 0;
}
