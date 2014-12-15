#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 35

int binary[MAX_NUMBER];
int combination[MAX_NUMBER][MAX_NUMBER];

int binary_count(int number) {
    int i, lenth, j;
    int binary_sum = 0;
    int zero_number;
    lenth = 0;
    while (number) {
        binary[++lenth] = number % 2;
        number = number >> 1;
    }
    for (i = 1; i < lenth - 1; i++) {
        for (j = i / 2 + 1; j <= i ; j++) {
            binary_sum += combination[i][j];
        }
    }
    zero_number = 0;
    for (i = lenth - 1; i >= 1; i--) {
        if (binary[i]) {
            for (j = (lenth + 1) / 2 - (zero_number + 1); j <= i - 1; j++) {
                binary_sum += combination[i - 1][j];
            }
        }
        else {
            zero_number++;
        }
    }
    return binary_sum;
}

int main() {

    int i ,j;
    int start, finish;
    int start_number, finish_number;
    memset(combination, 0, sizeof(combination));
    for (i = 0 ; i < MAX_NUMBER; i++) {
        for (j = 0; j <= i ; j++) {
            if (i == j || j == 0) {
                combination[i][j] = 1;
            }
            else {
                combination[i][j] = combination[i - 1][j] + combination[i - 1][j - 1];
            }
        }
    }
    scanf("%d%d", &start, &finish);
    start_number = binary_count(start - 1);
    finish_number = binary_count(finish);
    printf("%d\n", finish_number - start_number);  return 0;
}
