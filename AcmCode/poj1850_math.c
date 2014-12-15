#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 30

int combination[MAX_NUMBER][MAX_NUMBER];
char word[MAX_NUMBER];

void calculateCombination() {
    int i, j;
    for (i = 0; i < MAX_NUMBER; i++) {
        for (j = 0; j <= i; j++) {
            if (!j || j == i) {
                combination[i][j] = 1;
            }
            else {
                combination[i][j] = combination[i - 1][j - 1] + combination[i - 1][j];
            }
        }
    }
}

int judge_ok() {
    int i;
    int lenth;
    lenth = strlen(word);
    for (i = 0; i < lenth - 1; i++) {
        if (word[i] >= word[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int code() {
    int i, j;
    int lenth , distance;
    int code_number;
    char ch;
    lenth = strlen(word);
    code_number = 0;
    for (i = 1 ; i < lenth; i++ ) {
        code_number += combination[26][i];
    }
    for (i = 0; i < lenth; i++) {
        ch = (!i) ? 'a': word[i - 1] + 1;
        while (ch <= word[i] - 1) {
            code_number += combination['z' - ch ][lenth - i - 1];
            ch++;
        }
    }
    return code_number + 1;
}

int main() {

    int i, j, ok;
    int code_number;
    calculateCombination();
    while (scanf("%s", word) != EOF) {
        ok = judge_ok();
        if (ok) {
            code_number = code();
            printf("%d\n", code_number);
        }
        else {
            printf("0\n");
            return 0;
        }
    }
    return 0;
}
