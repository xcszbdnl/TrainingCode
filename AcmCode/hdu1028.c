#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 155

int dp[MAX_NUMBER][MAX_NUMBER];

int main() {

    int number;
    int i , j, k;
    for (i = 1; i <= MAX_NUMBER; i++) {
        dp[1][i] = 1;
        dp[i][0] = 1;
    }
    for (i = 2; i < 125; i++) {
        for (j = 1; j < 125; j++) {
            for (k = 0; k * i <= j; k++) {
                dp[i][j] += dp[i - 1][j - k * i];
            }
        }
    }
    while (scanf("%d", &number) != EOF) {
        printf("%d\n", dp[number][number]);
    }
}
