#include <stdio.h>

#define MAX_NUMBER 400


int bowling[MAX_NUMBER][MAX_NUMBER];
int sums[MAX_NUMBER][MAX_NUMBER];



int main() {

    int rows, max;
    int i, j;
    scanf("%d", &rows);
    for (i = 1; i <= rows; i++) {
        for (j = 1; j <= i; j++) {
            scanf("%d", &bowling[i][j]);
        }
    }
    for (i = 1; i <= rows; i++) {
        sums[rows][i] = bowling[rows][i];
    }
    for (i = rows - 1; i >= 1; i--) {
        for (j = 1; j <= i; j++) {
            if (sums[i + 1][j] > sums[i + 1][j + 1]) {
                max = sums[i + 1][j];
            }
            else {
                max = sums[i + 1][j + 1];
            }
            sums[i][j] = max + bowling[i][j];
        }
    }
    printf("%d\n", sums[1][1]);
}
