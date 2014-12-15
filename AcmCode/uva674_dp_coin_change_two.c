#include <stdio.h>


#define MAX_NUMBER 7500

int dp[MAX_NUMBER][MAX_NUMBER];
int coin[5] = {1, 5, 10, 25, 50};


int main() {
    int i, j;
    int k, money;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < MAX_NUMBER; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = 0;
            }
        }
    }

    for (i = 1; i < 5; i++) {
        for (j = 1; j < MAX_NUMBER; j++) {
            for (k = 0; k * coin[i] <= j; k++) {
                dp[i][j] += dp[i - 1][j - k * coin[i]];
            }
        }
    }
    while (scanf("%d", &money) != EOF) {
        for (i = 4; i >= 0; i--) {
            if (dp[i][money] != 0) {
                break;
            }
        }
        printf("%d\n", dp[i][money]);
    }
    return 0;
}
